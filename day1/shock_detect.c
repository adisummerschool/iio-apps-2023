#include <stdio.h>
#include <iio.h>
#include <time.h>

#define URI "ip:10.76.84.240"
#define THRESHOLD 600

int getAxis(struct iio_channel *channel)
{
	char raw[5] = {0};
	const char *attr = iio_channel_get_attr(channel, 0);
	iio_channel_attr_read(channel, attr, raw, 5);
	return atoi(raw);
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
	
	int prevX = 0, prevY = 0, prevZ = 0;
	while (true)
	{
		// Get axis values
		int x = getAxis(xpos) - getAxis(xneg);
		int y = getAxis(ypos) - getAxis(yneg);
		int z = getAxis(zpos) - getAxis(zneg);

		// Detect shake
		if (abs(x - prevX) > THRESHOLD ||
			abs(y - prevY) > THRESHOLD ||
			abs(z - prevZ) > THRESHOLD)
		{
			char buff[20];
			struct tm *sTm;

			time_t now = time(0);
			sTm = gmtime(&now);

			strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
			printf ("%s %s\n", buff, "Shake detected!");
		}

		prevX = x;
		prevY = y;
		prevZ = z;

		// Print to console
		// printf(" x: %4d | y: %4d | z: %4d\r", x, y, z);
		// fflush(stdout);
	}

	iio_context_destroy(ctx);
	return 0;
}