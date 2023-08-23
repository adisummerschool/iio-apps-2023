#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.209"

int main() {

	unsigned int ctx_count;

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	printf("\n");
	
	ctx_count = iio_context_get_attrs_count(ctx);

	for(int i=0; i<ctx_count; i++){
		iio_context_get_attr(ctx, i, &ctx_name, &ctx_val); 
		printf("ctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}

	printf("\n");
	
	iio_context_destroy(ctx);

	return 0;
}
