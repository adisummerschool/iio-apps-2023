#include <stdio.h>
#include <string.h>
#include <iio.h>

#define URI "ip:10.76.84.195"

#define FULL_SCALE_G 1

int getRaw(struct iio_channel *chn)
{
    char buffer_read[100] = {};
    iio_channel_attr_read(chn, "raw", buffer_read, 100);
    return atoi(buffer_read);
}


float voltage(int raw)
{
    	return 1.0* raw * 25.0 / 10.0 / 4095.0;
}

float acceleration(int raw)
{
    	return (1.0* raw / 4095.0) * 1.0 * FULL_SCALE_G * 9.8;
}


void show_info(struct iio_channel *chn){

	int raw = getRaw(chn);
	printf("xpoz r:%d v:%.4f acc:%.4f \n", raw, voltage(raw), acceleration(raw));
	 raw = getRaw(chn);
	printf("xneg r:%d v:%.4f acc:%.4f \n", raw, voltage(raw), acceleration(raw));
	 raw = getRaw(chn);
	printf("ypoz r:%d v:%.4f acc:%.4f \n", raw, voltage(raw), acceleration(raw));
	 raw = getRaw(chn);
	printf("yneg r:%d v:%.4f acc:%.4f \n", raw, voltage(raw), acceleration(raw));
	 raw = getRaw(chn);
	printf("zpoz r:%d v:%.4f acc:%.4f \n", raw, voltage(raw), acceleration(raw));
	 raw = getRaw(chn);
	printf("zneg r:%d v:%.4f acc:%.4f \n", raw, voltage(raw), acceleration(raw));
	printf("\n");
}

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

	int chanCount = iio_device_get_channels_count(dev);

	for (int i = 0; i < chanCount; i++)
	{
		chn = iio_device_get_channel(dev, i);
		printf("Channel %d:\n", i);
		show_info(chn);
	}
    
    	return 0;
}