/**
 * target output:
 *
 * x: <val g> | y: <val g> | z: <val g>
 */


	// voltage0 : yneg;
	// voltage1 : xpos;
	// voltage2 : zpos;
	// voltage3 : xneg;
	// voltage4 : zneg;
	// voltage5 : ypos;


#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.240"

int getAxis(struct iio_channel *channel)
{
	char raw[5] = {0};
	char *attr = iio_channel_get_attr(channel, 0);
	iio_channel_attr_read(channel, attr, raw, 5);
	return atoi(raw);
}

void calibrate(int x, int y, int z)
{
	int threshold = 100;
	char *outBuffer = "";
	
	if (x > threshold || x < -threshold)
	{
		outBuffer += "x: ";
		outBuffer += x;
		outBuffer += " | ";
	}
	if (y > threshold || y < -threshold)
	{
		outBuffer += "y: ";
		outBuffer += y;
		outBuffer += " | ";
	}
	if (z > threshold || z < -threshold)
	{
		outBuffer += "z: ";
		outBuffer += z;
		outBuffer += " | ";
	}
}

int main()
{
	// Get the iio context
	struct iio_context *ctx;
	ctx = iio_create_context_from_uri(URI);
	if (ctx == NULL)
	{
		printf("Context couldn't be returned.\nExiting...");
		return -1;
	}

	// Get device (AD5592R)
	const char *deviceName = "ad5592r_s";
	struct iio_device *ad5592r = iio_context_find_device(ctx, "ad5592r_s");
	if (ad5592r == NULL)
	{
		printf("%s not found!\nExiting...", deviceName);
		return -1;
	}
	printf("%s found!\n", deviceName);

	// Get channels
	struct iio_channel *xpos = iio_device_find_channel(ad5592r, "voltage1", false);
	struct iio_channel *xneg = iio_device_find_channel(ad5592r, "voltage3", false);

	struct iio_channel *ypos = iio_device_find_channel(ad5592r, "voltage5", false);
	struct iio_channel *yneg = iio_device_find_channel(ad5592r, "voltage0", false);

	struct iio_channel *zpos = iio_device_find_channel(ad5592r, "voltage2", false);
	struct iio_channel *zneg = iio_device_find_channel(ad5592r, "voltage4", false);

	printf("Channels found!\n");
	while (true)
	{
		int x = getAxis(xpos) - getAxis(xneg);
		int y = getAxis(ypos) - getAxis(yneg);
		int z = getAxis(zpos) - getAxis(zneg);

		// calibration helper
		calibrate(x, y, z);

		// Print to console
		// printf(" x: %4d | y: %4d | z: %4d\r", x, y, z);
		// fflush(stdout);
	}

	iio_context_destroy(ctx);
	return 0;
}
