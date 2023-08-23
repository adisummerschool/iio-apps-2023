#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.209"

int main() {

	unsigned int ctx_count;
	unsigned int dev_count;

	const char *dev_id;
	const char *dev_name;
	const char *dev_attr;
	const char *chan_id; 
	const char *chan_attr;
	char valoare[10];

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chan;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	
	ctx_count = iio_context_get_attrs_count(ctx);

	for(int i=0; i<ctx_count; i++){
		iio_context_get_attr(ctx, i, &ctx_name, &ctx_val); 
		printf("ctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}

	printf("\n");
	
	dev = iio_context_get_device(ctx, 0);

	dev_id = iio_device_get_id(dev);
	dev_name = iio_device_get_name(dev); 
	
	printf("%s : %s\n", dev_id, dev_name);
	
	unsigned int chan_cnt = iio_device_get_channels_count(dev);
	printf("%d\n", chan_cnt);

	for(int i=0; i<chan_cnt; i++){
		chan = iio_device_get_channel(dev, i);
		chan_id = iio_channel_get_id(chan);
		chan_attr = iio_channel_get_attr(chan, 0);

		iio_channel_attr_write(chan, chan_attr, "87");
		iio_channel_attr_read(chan, chan_attr, valoare, 10);
		printf("%s : %s\n", chan_id, chan_attr);
		printf("%s\n", valoare);
	}
	
	iio_context_destroy(ctx);

	return 0;
}
