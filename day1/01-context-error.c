#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.153"

int main() {
	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;

	iio_library_get_version(&major, &minor, git_tag);
	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	struct iio_context *ctx;

	ctx = iio_create_context_from_uri(URI);

	// 1. Handle when context is not available
	if(!ctx) {
		printf("[ERROR] : Can't create context with provided URI: %s", URI);
		return 1;
	}

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);

	return 0;
}

