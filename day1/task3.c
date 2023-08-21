#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.156"

int main()
{
	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	struct iio_context *ctx;
	iio_library_get_version(&major, &minor, git_tag);
	printf("libiio version: %d.%d - %s\n", major, minor, git_tag);
	ctx = iio_create_context_from_uri(URI);
	if (ctx == NULL)
	{
		fprintf(stderr, "Failed to create context from URI: %s\n", URI);
		return -1;
	}
	int dev_count = iio_context_get_devices_count(ctx);
	for (int i = 0; i < dev_count; i++)
	{
		struct iio_device *dev = iio_context_get_device(ctx, i);
		printf("Device %d: %s\n", i, iio_device_get_name(dev));
		int ch_count = iio_device_get_channels_count(dev);
		for (int j = 0; j < ch_count; j++)
		{
			struct iio_channel *ch = iio_device_get_channel(dev, j);
			const char *ch_name = iio_channel_get_name(ch);
			const char *ch_id = iio_channel_get_id(ch);
			printf("  Channel %d: Name: %s, ID: %s\n", j, ch_name ? ch_name : "(null)", ch_id ? ch_id : "(null)");
			int attr_count = iio_channel_get_attrs_count(ch);
			for (int k = 0; k < attr_count; k++)
			{
				const char *attr_name = iio_channel_get_attr(ch, k);
				char attr_val[1024];
				iio_channel_attr_read(ch, attr_name, attr_val, sizeof(attr_val));
				printf("    Attribute %d: %s - %s\n", k, attr_name, attr_val);
			}
		}
	}
	iio_context_destroy(ctx);
	return 0;
}