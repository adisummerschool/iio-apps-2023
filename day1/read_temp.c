#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.240"

const char *deviceName = "xadc";

int main()
{
	struct iio_context *ctx;
	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL)
	{
		printf("Context couldn't be returned.\nExiting...");
		return -1;
	}

	// Check if device exists
	struct iio_device *dev = iio_context_find_device(ctx, deviceName);
	if (dev == NULL)
	{
		printf("%s not found!\nExiting...", deviceName);
		return -1;
	}
	printf("%s found!\n", deviceName);

	// Get channel
	struct iio_channel *ch = iio_device_find_channel(dev, "temp0", false);
	if (ch == NULL)
	{
		printf("Channel not found!\nExiting...");
		return -1;
	}
	
	const char *chName = iio_channel_get_id(ch);
	char buff[50];

	// Get channel attributes
	iio_channel_attr_read(ch, "offset", buff, 50);
	int offset = atoi(buff);

	iio_channel_attr_read(ch, "raw", buff, 50);
	int raw = atoi(buff);

	iio_channel_attr_read(ch, "scale", buff, 50);
	int scale = atoi(buff);

	// Calculate temperature
	double temperature = ((raw + offset) * scale) / 1000;

	// Print results
	printf("Channel: %s\noffset\t%d\nraw\t%d\nscale\t%d\n", chName, offset, raw, scale);
	printf("-> Temperature: %f\nC", temperature);

	iio_context_destroy(ctx);
	return 0;
}