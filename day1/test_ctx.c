#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.209"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	struct iio_context *ctx;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

    if (ctx == NULL) {
        fprintf(stderr, "Failed to create context from URI: %s\n", URI);
        return -1;
    }

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);

	iio_context_destroy(ctx);

	return 0;
}
