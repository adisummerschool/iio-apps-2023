//Challenge 3: Can you make it so it reads device/channel attributes ? Redo the 
//             script to write 1,2,3,4... to a raw channel attribute.

#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.201"

int main() {

	const char *ctx_name;
	const char *ctx_val;
	const char *description;
	struct iio_context *ctx;
	struct iio_device *dev;

	ctx = iio_create_context_from_uri(URI);
	dev = iio_context_find_device(ctx, "ad5592r_s");

	for(int i = 0; i < iio_device_get_channels_count(dev); ++i) {
		char voltage_nr[50];
		sprintf(voltage_nr, "voltage%d", i);
		struct iio_channel* channel = iio_device_find_channel(dev, voltage_nr, false);
		const char* chn_name = iio_channel_get_id(channel);

		printf("\tCurrent channel %s\n", chn_name);
	
		for(int j = 0; j < iio_channel_get_attrs_count(channel); ++j) {
			const char* crn_attr = iio_channel_get_attr(channel, j);

			char buff[50];
			iio_channel_attr_read(channel, crn_attr, buff, 50);
			printf("\t\tattr %d: %s value : %s\n", j, crn_attr, buff);
		}
	}
	

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	iio_context_get_attr(ctx,0,&ctx_name,&ctx_val); 
	printf("ctx attr %d: %s - %s\n" ,0, ctx_name, ctx_val);
	iio_context_destroy(ctx);

	return 0;
}
