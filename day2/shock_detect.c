#include <stdio.h>
#include <string.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.195"

#define FULL_SCALE_G 1

int getRaw(struct iio_channel *chn)
{
	char buffer_read[100] = {};
	iio_channel_attr_read(chn, "raw", buffer_read, 100);
	return atoi(buffer_read);
}

float acceleration(int raw)
{
    	return (1.0* raw / 4095.0) * 1.0 * FULL_SCALE_G * 9.8;
}

float getXAcc(struct iio_device *dev){

	struct iio_channel *chn;
	int raw1, raw2;
	
	chn = iio_device_get_channel(dev, 0);
	raw1 = getRaw(chn);

	chn = iio_device_get_channel(dev, 1);
	raw2 = getRaw(chn);

	return acceleration(raw1) - acceleration(raw2);
}

float getYAcc(struct iio_device *dev){

	struct iio_channel *chn;
	int raw1, raw2;
	
	chn = iio_device_get_channel(dev, 2);
	raw1 = getRaw(chn);

	chn = iio_device_get_channel(dev, 3);
	raw2 = getRaw(chn);

	return acceleration(raw1) - acceleration(raw2);
}

float getZAcc(struct iio_device *dev){

	struct iio_channel *chn;
	int raw1, raw2;
	
	chn = iio_device_get_channel(dev, 4);
	raw1 = getRaw(chn);

	chn = iio_device_get_channel(dev, 5);
	raw2 = getRaw(chn);

	return acceleration(raw1) - acceleration(raw2);
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

	//todo ..

	int detected = 0;
	while(!detected){

	}

    
    	return 0;
}