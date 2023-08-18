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
	//part 4(last part)

	
	dev = iio_context_find_device(ctx, "xadc");
	int n = iio_device_get_channels_count(dev);
	for(int i = 0; i < n; i++)
	{
		chn = iio_device_get_channel(dev, i);
		if(iio_channel_find_attr(chn, "offset") != NULL)
		{
			iio_channel_attr_read(chn, "raw", buffer_read, 100);
			raw = atoi(buffer_read);
			iio_channel_attr_read(chn, "scale", buffer_read, 100);
			scale = atoi(buffer_read);
			iio_channel_attr_read(chn, "offset", buffer_read, 100);
			offset = atoi(buffer_read);
			temp = (float)((raw + offset) * scale);
			printf("Temp is %.3f\n", temp/1000);
		}
		// printf("%d\n", raw);
		// for(int j = 0; j < iio_channel_get_attrs_count(chn); j++)
		// {
		// 	printf("%s\n",iio_channel_get_attr(chn, j));
		// }
	}
	iio_context_destroy(ctx);

	return 0;
}
