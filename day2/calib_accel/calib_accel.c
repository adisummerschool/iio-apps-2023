#include <stdio.h>
#include <string.h>
#include <iio.h>

#define URI "ip:10.76.84.195"

#define FULL_SCALE_G 1

int is_calibrated(struct iio_channel *chn);
float get_accel(struct iio_channel *chn);

int main()
{
    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *chn;

    ctx = iio_create_context_from_uri(URI);
    
    dev = iio_context_find_device(ctx, "ad5592r_s");

    int n = iio_device_get_channels_count(dev);

    int k[3] = {0, 0, 0};
    int all = 0;
    while(all == 0)
    {
        for(int i = 0; i < n; i += 2)
        {
            chn = iio_device_get_channel(dev, i);
            if(is_calibrated(chn))
            {
                printf("POT%d clockwise ", (i/2)+1);
            }
            else
            {
                chn = iio_device_get_channel(dev, i+1);
                if(is_calibrated(chn))
                {
                    printf("POT%d counter-clockwise ", (i/2)+1);
                }
                else
                {
                    printf("POT%d center ", (i/2)+1);
                    k[i/2] = 1;
                }
            }
        }
        if(k[0] == 1 && k[1] == 1 && k[2] == 1)
            all = 1;
        printf("\n");
        sleep(5);
    }
    printf("Calibrated!\n");

    return 0;
}

float get_accel(struct iio_channel *chn)
{
    char buffer_read[100] = {};
    int raw;
    iio_channel_attr_read(chn, "raw", buffer_read, 100);
    raw = atoi(buffer_read);
    return ((float)raw/4095)*FULL_SCALE_G*(9.8);
}

int is_calibrated(struct iio_channel *chn)
{
    if(get_accel(chn) < 0.1)
        return 0;
    else
        return -1;
}