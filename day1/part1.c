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
    return 0;
}