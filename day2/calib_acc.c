#include<stdio.h>
#include<stdlib.h>
#include<iio.h>
#include<unistd.h>

#define URI "ip:10.76.84.208"

bool readChannel(struct iio_channel *chn[], int axis)
{
	char chn_raw[50];

	switch (axis)
	{
	case 0:
		iio_channel_attr_read(chn[0], "raw", chn_raw, 50);
		if (atoi(chn_raw) > 100){
			printf("POT1: Clockwise ");
		}
		iio_channel_attr_read(chn[1], "raw", chn_raw, 50);
		if (atoi(chn_raw) > 100){
			printf("POT1: Counter-clockwise ");
		}
		else{
			printf("POT1: Centered. ");
		}
		break;
	case 2:
		iio_channel_attr_read(chn[2], "raw", chn_raw, 50);
		if (atoi(chn_raw) > 100){
			printf("POT2: Clockwise ");
		}
		iio_channel_attr_read(chn[3], "raw", chn_raw, 50);
		if (atoi(chn_raw) > 100){
			printf("POT2: Counter-clockwise ");
		}
		else{
			printf("POT2: Centered. ");
		}
		break;	
	case 4:
		iio_channel_attr_read(chn[4], "raw", chn_raw, 50);
		if (atoi(chn_raw) < 4000){
			printf("POT3: Clockwise \n");
		}
		iio_channel_attr_read(chn[5], "raw", chn_raw, 50);
		if (atoi(chn_raw) > 100){
			printf("POT3: Counter-clockwise \n");
		}
		else{
			printf("POT3: Centered. \n");
		}
		break;	
	
	default:
		break;
	}
}

int main() {

	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn[6];

	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL)
	{
		printf("Cannot connect to the board.\n");
		return 1;
	}

	dev = iio_context_find_device(ctx, "ad5592r_s");

	chn[0] = iio_device_find_channel(dev, "voltage0", false);
	chn[1] = iio_device_find_channel(dev, "voltage1", false);
	chn[2] = iio_device_find_channel(dev, "voltage2", false);
	chn[3] = iio_device_find_channel(dev, "voltage3", false);
	chn[4] = iio_device_find_channel(dev, "voltage4", false);
	chn[5] = iio_device_find_channel(dev, "voltage5", false);


	printf("Calibrating.\n");
	
	while (1){
		system("clear");
		
		readChannel(chn, 0);
		readChannel(chn, 2);
		readChannel(chn, 4);
		
		usleep(150000);
	
	}
	iio_context_destroy(ctx);

	return 0;
}
