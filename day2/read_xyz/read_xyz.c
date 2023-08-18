#include <stdio.h>
#include <string.h>
#include <iio.h>

#define URI "ip:10.76.84.195"

#define FULL_SCALE_G 1

int raw(struct iio_channel *chn);
int voltage(struct iio_channel *chn);
float acceleration(struct iio_channel *chn);

int main()
{
    struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn;

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

    chn = iio_device_get_channel(dev, 0);
    if(raw(chn) != 1)
        printf("xpoz %d %d %f", raw(chn), voltage(chn), acceleration(chn));
    chn = iio_device_get_channel(dev, 1);
    if(raw(chn) != 1)
        printf("xpoz %d %d %f", raw(chn), voltage(chn), acceleration(chn));
    chn = iio_device_get_channel(dev, 2);
    if(raw(chn) != 1)
        printf("xpoz %d %d %f", raw(chn), voltage(chn), acceleration(chn));
    chn = iio_device_get_channel(dev, 3);
    if(raw(chn) != 1)
        printf("xpoz %d %d %f", raw(chn), voltage(chn), acceleration(chn));
    chn = iio_device_get_channel(dev, 4);
    if(raw(chn) != 1)
        printf("xpoz %d %d %f", raw(chn), voltage(chn), acceleration(chn));
    chn = iio_device_get_channel(dev, 5);
    if(raw(chn) != 1)
        printf("xpoz %d %d %f", raw(chn), voltage(chn), acceleration(chn));

    return 0;
}

int raw(struct iio_channel *chn)
{
    char buffer_read[100] = {};
    iio_channel_attr_read(chn, "raw", buffer_read, 100);
    if(buffer_read)
        return atoi(buffer_read);
    else{
        printf("Error at reading raw value.\n");
        return -1;
    }
}

int voltage(struct iio_channel *chn)
{
    return ((raw(chn)*25)/10)/4095;
}

float acceleration(struct iio_channel *chn)
{
    return (float)(raw(chn)/4095)*FULL_SCALE_G*(9.8);
}