#include <stdio.h>
#include <string.h>
#include <iio.h>

#define URI "ip:10.76.84.244"

int main() {

	unsigned int major;
	unsigned int minor;
	unsigned int attr_count;
	unsigned int dev_count;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	char *chn_read;
	const char *chn_attr = "raw";
	char *cur_attr;
	char buffer[1];
	char buffer_read[100] = {};

	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	iio_context_get_attr(ctx,0,&ctx_name,&ctx_val); 
	printf("ctx attr %d: %s - %s\n" ,0, ctx_name, ctx_val);
	attr_count = iio_context_get_attrs_count(ctx);
	//printf("attr_count = %d\n", attr_count);
	int ret = 0;
	float temp;
	int raw, scale, offset;
	for(int i = 0; i < attr_count; i++)
	{
		ret = iio_context_get_attr(ctx, i, &ctx_name, &ctx_val);
		if(ret)
		{
			printf("Attribute doesn't exist.");
			return 0;
		}
		printf("ctx attr no.%d %d: %s - %s\n", i ,i, ctx_name, ctx_val);
	}
	dev_count = iio_context_get_devices_count(ctx);
	for(int i = 0; i < dev_count; i++)
	{
		printf("Device %d\n", i);
		dev = iio_context_get_device(ctx, i);
		if(dev)
		{
			for(int j = 0; j < iio_device_get_attrs_count(dev); j++)
			{
				printf("%s\n", iio_device_get_attr(dev, j));
			}
			if(iio_device_get_channels_count(dev) > 0)
			{
				printf("Channels :\n");
				for(int k = 0; k < iio_device_get_channels_count(dev); k++)
				{
					chn = iio_device_get_channel(dev, k);
					chn_attr = iio_channel_get_attr(chn, 0);
					//iio_channel_attr_read(chn, chn_attr, chn_read, strlen(chn_attr));
					//printf("raw = %s\n", chn_attr);
				}
			}
		}
		else
		{
			printf("The device doesn't exist.");
			return 0;
		}
	}

	iio_context_destroy(ctx);

	return 0;
}
