#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.239"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	int c_attr_n;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	if(ctx == NULL){
		fprintf(stderr, "Failed to create context from URI: %s\n", URI);
		return -1;
	}
	c_attr_n = iio_context_get_attrs_count(ctx);

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);

	for(int i = 0; i< c_attr_n; i++)
	{	int device_n =  iio_context_get_devices_count(ctx);
		iio_context_get_attr(ctx,i,&ctx_name,&ctx_val); 
		printf("ctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}
	iio_context_destroy(ctx);

	return 0;
}
