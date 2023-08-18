#include <stdio.h>
#include <string.h>
#include <iio.h>

#define URI "ip:10.76.84.240"

int main()
{
	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;

	// Get libiio version
	iio_library_get_version(&major, &minor, git_tag);
	printf("libiio version: %d.%d - %s \n", major, minor, git_tag);

	// Get the iio context
	ctx = iio_create_context_from_uri(URI);
	if (ctx == NULL)
	{
		printf("Context couldn't be returned.\nExiting...");
		return -1;
	}

	// Get all attributes
	int attr_cnt = iio_context_get_attrs_count(ctx);
	printf("Attributes (%d):\n", attr_cnt);
	for (int i = 0; i < attr_cnt; ++i)
	{
		iio_context_get_attr(ctx, i, &ctx_name, &ctx_val);
		printf("ctx attr %d: %s - %s\n", i, ctx_name, ctx_val);
	}

	// Get number of devices
	int dev_cnt = iio_context_get_devices_count(ctx);
	if (dev_cnt == 0)
	{
		printf("No. of devices couldn't be retrieved!\nExiting...");
		return -1;
	}
	printf("dev cnt: %d\n", dev_cnt);

	struct iio_device *ad5592r = NULL; // save AD5592R device
	// Parse devices
	for (int i = 0; i < (dev_cnt - 1); ++i)
	{
		struct iio_device *dev = iio_context_get_device(ctx, i);

		// Get device's name
		const char *dev_name = iio_device_get_name(dev);
		printf("Device name: %s\n", dev_name);

		// Save AD5592R
		if (!strcmp(dev_name, "ad5592r_s"))
		{
			ad5592r = dev;
		}

		// Get channel count
		int ch_cnt = iio_device_get_channels_count(dev);

		// Print all channels
		for (int ch = 0; ch < ch_cnt; ++ch)
		{
			struct iio_channel *chn = iio_device_get_channel(dev, ch);
			const char *chn_id = iio_channel_get_id(chn);
			printf("Channel ID: %s\n", chn_id);
		}
		printf("\n");
	}

	// Check if AD5592R was found
    if (ad5592r == NULL)
    {
        printf("AD5592R not found!\nExiting...");
        return -1;
    }
    printf("AD5592R Found!\n--------------\n");

	// Iterate through its channels
    int ch_cnt = iio_device_get_channels_count(ad5592r);
    for (int i = 0; i < ch_cnt; ++i)
    {
        struct iio_channel *chn = iio_device_get_channel(ad5592r, i);
        const char *chn_id = iio_channel_get_id(chn);
        printf("Channel ID: %s\n", chn_id);

		// Read raw value
        const char *raw_val;
        iio_channel_attr_read(chn, "raw", raw_val, 10);
        printf("Raw value: %s\n", raw_val);
    }

    iio_context_destroy(ctx);
	return 0;
}
