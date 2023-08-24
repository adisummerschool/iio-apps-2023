#include <stdio.h>
#include <iio.h>
#include <string.h>

#define URI "ip:10.76.84.209"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	int ret;
	int ctx_attr_c, dev_c;
	float temp;
	int raw, offset;
	float scale;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL) {
		printf("Context from URI failed\n");
		// get everything out from stdout buffer
		return -1;
	}

	ctx_attr_c = iio_context_get_attrs_count(ctx);


	for (int i = 0; i < ctx_attr_c; i++) {
		const char *name;
		const char *val;
		ret = iio_context_get_attr(ctx, i, &name, &val);
		printf("Context attribute %d:\n%s: %s\n\n", i, name, val);
	}
	
	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	iio_context_get_attr(ctx,0,&ctx_name,&ctx_val); 
	printf("ctx attr %d: %s - %s\n" ,0, ctx_name, ctx_val);


	dev_c = iio_context_get_devices_count(ctx);

	for (int dev_num = 0; dev_num < dev_c; dev_num++) {
		struct iio_device *dev = iio_context_get_device(ctx, dev_num);
		const char *dev_name = iio_device_get_name(dev);
		int dev_chan_c = iio_device_get_channels_count(dev);
		int dev_attr_c = iio_device_get_attrs_count(dev);

		printf("Device %d - %s:\n", dev_num, dev_name);

		for (int dev_chan_index = 0; dev_chan_index < dev_chan_c; dev_chan_index++) {
			raw = 0;
			scale = 0;
			offset = 0;
			struct iio_channel *chan = iio_device_get_channel(dev, dev_chan_index);
			const char *chan_name = iio_channel_get_id(chan);
			int chan_attr_c = iio_channel_get_attrs_count(chan);

			printf("Channel %s:\n", chan_name);

			for (int chan_attr_i = 0; chan_attr_i < chan_attr_c; chan_attr_i++) {
				const char *chan_attr = iio_channel_get_attr(chan, chan_attr_i);
				char *chan_attr_val = (char *)malloc(15);
				iio_channel_attr_read(chan, chan_attr, chan_attr_val, 15);

				if (strcmp("raw", chan_attr) == 0) {
					raw = atoi(chan_attr_val);
				} else if (strcmp("scale", chan_attr) == 0) {
					scale = atof(chan_attr_val);
				} else if (strcmp("offset", chan_attr) == 0) {
					offset = atoi(chan_attr_val);
				}

				printf("Attribute %s = %s\n", chan_attr, chan_attr_val);
			}

			if (strcmp("xadc", dev_name) == 0) {
				temp = (raw + offset) * scale / 1000;
				printf("\ntemp = %f\n\n", temp);
			}
		}


		printf("\nDevice specific attributes:\n");
		for (int dev_attr_i = 0; dev_attr_i < dev_attr_c; dev_attr_i++) {
			const char *dev_attr = iio_device_get_attr(dev, dev_attr_i);
			char *dev_attr_val = (char *)malloc(sizeof(long long));
			iio_device_attr_read(dev, dev_attr, dev_attr_val, sizeof(long long));

			printf("Attribute %s = %s\n", dev_attr, dev_attr_val);
		}
		printf("\n\n");
	}

	iio_context_destroy(ctx);

	return 0;
}
