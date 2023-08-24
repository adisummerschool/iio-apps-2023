#include<stdio.h>
#include<stdlib.h>
#include<iio.h>
#include<unistd.h>
#include<time.h>

#define URI "ip:10.76.84.208"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn0;
	struct iio_channel *chn1;
	struct iio_channel *chn2;
	struct iio_channel *chn3;
	struct iio_channel *chn4;
	struct iio_channel *chn5;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

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

	char chn0_voltage[50];
	char chn1_voltage[50];
	char chn2_voltage[50];
	char chn3_voltage[50];
	char chn4_voltage[50];
	char chn5_voltage[50];
	while(1)
	{
		system("clear");
		iio_channel_attr_read(chn0, "raw", chn0_voltage, 50);
		printf("Xpoz = %s %lf %lf\n", chn0_voltage, (atoi(chn0_voltage) * 2.5) / 4095, atoi(chn0_voltage) / 4095.0);
		iio_channel_attr_read(chn1, "raw", chn1_voltage, 50);
		printf("Xneg = %s %lf %lf\n", chn1_voltage, (atoi(chn1_voltage) * 2.5) / 4095, atoi(chn1_voltage) / 4095.0);
		iio_channel_attr_read(chn2, "raw", chn2_voltage, 50);
		printf("Ypoz = %s %lf %lf\n", chn2_voltage, (atoi(chn2_voltage) * 2.5) / 4095, atoi(chn2_voltage) / 4095.0);
		iio_channel_attr_read(chn3, "raw", chn3_voltage, 50);
		printf("Yneg = %s %lf %lf\n", chn3_voltage, (atoi(chn3_voltage) * 2.5) / 4095, atoi(chn3_voltage) / 4095.0);
		iio_channel_attr_read(chn4, "raw", chn4_voltage, 50);
		printf("Zpoz = %s %lf %lf\n", chn4_voltage, (atoi(chn4_voltage) * 2.5) / 4095, atoi(chn4_voltage) / 4095.0);
		iio_channel_attr_read(chn5, "raw", chn5_voltage, 50);
		printf("Zneg = %s %lf %lf\n", chn5_voltage, (atoi(chn5_voltage) * 2.5) / 4095, atoi(chn5_voltage) / 4095.0);
		usleep(150000);
	}
	
	

	iio_context_destroy(ctx);

	return 0;
}
