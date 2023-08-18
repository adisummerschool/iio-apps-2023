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

// float raw2volts(int raw)
// {
// 	return raw * 2.5 / 4095;
// }

float raw2accel(int raw)
{
	return (float)raw / 4095;
}

float getAxis(struct iio_channel *channel)
{
	char raw[4] = {0};
	char *attr = iio_channel_get_attr(channel, 0);
	iio_channel_attr_read(channel, attr, raw, 10);
	return raw2accel(atoi(raw));
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
		float x = getAxis(xpos) - getAxis(xneg);
		float y = getAxis(ypos) - getAxis(yneg);
		float z = getAxis(zpos) - getAxis(zneg);

		// Print to console
		printf(" x: %7.4f | y: %7.4f | z: %7.4f\r", x, y, z);
		fflush(stdout);
	}

	iio_context_destroy(ctx);
	return 0;
}
