#include<stdio.h>
#include<stdlib.h>
#include<iio.h>

#define URI "ip:10.76.84.208"
#define THRESHOLD 0.85

float getAcc(const char chn_raw[])
{
	return atof(chn_raw)/4095 * 9.81;
}

bool isShock(const char chn_raw[])
{
	return getAcc(chn_raw) > THRESHOLD ? true : false;
}

int main() {

	struct iio_context *ctx;
	struct iio_device *dev;
	bool shock_detected = 0;
	char chn_voltage[50];
	struct iio_channel *chn0;
	struct iio_channel *chn1;
	struct iio_channel *chn2;
	struct iio_channel *chn3;
	struct iio_channel *chn4;
	struct iio_channel *chn5;

	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL)
	{
		printf("Cannot connect to the board.\n");
		return 1;
	}

	dev = iio_context_find_device(ctx, "ad5592r_s");
	chn0 = iio_device_find_channel(dev, "voltage0", false);
	chn1 = iio_device_find_channel(dev, "voltage1", false);
	chn2 = iio_device_find_channel(dev, "voltage2", false);
	chn3 = iio_device_find_channel(dev, "voltage3", false);
	chn4 = iio_device_find_channel(dev, "voltage4", false);
	chn5 = iio_device_find_channel(dev, "voltage5", false);
	

	while (!shock_detected)
	{
		for (int i = 0; i < 6 && !shock_detected; i++)
		{
			switch (i)
			{
				case 0:
					iio_channel_attr_read(chn0, "raw", chn_voltage, 50);
				break;
				case 1:
					iio_channel_attr_read(chn1, "raw", chn_voltage, 50);
				break;
				case 2:
					iio_channel_attr_read(chn2, "raw", chn_voltage, 50);
				break;
				case 3:
					iio_channel_attr_read(chn3, "raw", chn_voltage, 50);
				break;
				// case 4:
				// 	iio_channel_attr_read(chn4, "raw", chn_voltage, 50);
				// break;
				// case 5:
				// 	iio_channel_attr_read(chn5, "raw", chn_voltage, 50);
				// break;
			}
			if (isShock(chn_voltage))
			{
				shock_detected = true;
				printf("Shock detected.\n");
			}
		}
	}

	iio_context_destroy(ctx);

	return 0;
}
