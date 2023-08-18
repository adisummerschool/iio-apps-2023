#include <stdio.h>
#include <string.h>
#include <iio.h>

#define URI "ip:10.76.84.195"

#define FULL_SCALE_G 1

float get_accel(struct iio_channel *chn);

int main()
{
    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *chn;

    int sign = 0;
    float accel;

    char num[6] = {'x', 'x', 'y', 'y', 'z', 'z'};

    ctx = iio_create_context_from_uri(URI);
    if(!ctx)
        printf("URI ERROR");

    dev = iio_context_find_device(ctx, "ad5592r_s");
    if(!dev)
        printf("DEV ERROR");

    int n = iio_device_get_channels_count(dev);

    while(1)
    {
        for(int i = 0; i < n; i += 2)
        {
            chn = iio_device_get_channel(dev, i);
            accel = get_accel(chn);
            chn = iio_device_get_channel(dev, i+1);
            accel += get_accel(chn);
            if(accel > 0)
                printf("%c acceleration : %f\n", num[i], accel);
            else
                printf("%c acceleration : %f\n", num[i], accel);
        }
        printf("\n");
        sleep(3);
    }

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