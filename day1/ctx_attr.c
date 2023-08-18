//Challenge 2: Can you make it so it reads all context attributes?

#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.201"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;

	iio_library_get_version(&major, &minor, git_tag);

	ctx = iio_create_context_from_uri(URI);

	for(int i = 0; i < iio_context_get_attrs_count(ctx); ++i) {
		iio_context_get_attr(ctx, i, &ctx_name, &ctx_val);
		printf("libiio version: %d.%s - %s \n", i, ctx_name, ctx_val);
	}

	return 0;
}
