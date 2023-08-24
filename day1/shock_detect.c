#include <stdio.h>
#include<stdlib.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>

#define URI "ip:10.76.84.208"

#define SCALE 1

int is_shock(struct iio_channel *chn, float prev_val);
float get_accel(struct iio_channel *chn);

int main()
{
    struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn;

    unsigned int major;
	unsigned int minor;
	char git_tag[8];

    iio_library_get_version(&major, &minor, git_tag);
    printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

    ctx = iio_create_context_from_uri(URI);
    if(!ctx)
    {
        printf("Can't find specified URI.");
        return 0;
    }

    dev = iio_context_find_device(ctx, "ad5592r_s");
    if(!dev)
    {
        printf("Can't find ad5592r.");
        return 0;
    }

    int n = iio_device_get_channels_count(dev);
    int shock = 0;
    float prev[6];

    for(int i = 0; i < n; i++)
    {
        chn = iio_device_get_channel(dev, i);
        prev[i] = get_accel(chn);
    }

    while(shock == 0)
    {
        
        for(int i = 0; i < n; i++)
        {
            if(shock == 0)
            {
                chn = iio_device_get_channel(dev, i);
                if(is_shock(chn, prev[i]))
                {
                    printf("Shock detected!");
                    shock = 1;
                }
                else
                {
                    printf("Everything ok!\n");
                }
            }
        }
        //sleep(1);
    }

    return 0;
}

float get_accel(struct iio_channel *chn)
{
    char buffer_read[100] = {};
    int raw;
    iio_channel_attr_read(chn, "raw", buffer_read, 100);
    raw = atoi(buffer_read);
    return ((float)raw/4095)*SCALE*(9.8);
}

int is_shock(struct iio_channel *chn, float prev_val)
{
    float tmp_val;
    tmp_val = get_accel(chn);
    
    if(prev_val > tmp_val && prev_val-tmp_val > 0.9)
        return 1;
    
    if(prev_val < tmp_val && tmp_val-prev_val > 0.9)
        return 1;

    prev_val = tmp_val;

    return 0;
}