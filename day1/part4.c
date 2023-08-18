#include <stdio.h>
#include<stdlib.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.205"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	const char *dev_name;
	const char *dev_val;
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn;
	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
    
	ctx = iio_context_get_devices_count(URI);

	if (ctx == NULL){
		printf("The board is not available!\n");
		return 1;
	}

    // (raw + offset) * scale;
	bool ret_val;
	dev = iio_context_find_device(ctx, "xadc");
	chn = iio_device_find_channel(dev, "temp0", ret_val);



	char raw[50];
	char offset[50];
	char scale[50];
    const char *attr_name = iio_channel_get_attr(chn, 0);
	char raw_data;
	char *raw_data_pointer = (char*)malloc(50 * sizeof(char));
	iio_channel_attr_read(chn, "raw", raw, 50);
	iio_channel_attr_read(chn, "scale", scale, 50);
	iio_channel_attr_read(chn, "offset", offset, 50);

	int raw_int = atoi(raw);
	int offset_int = atoi(offset);
	int scale_int = atoi(scale);

	printf("Temperature = %d\n", (raw_int + offset_int) * scale_int / 1000);

	iio_context_destroy(ctx);
	free(raw_data_pointer);

	return 0;
}
