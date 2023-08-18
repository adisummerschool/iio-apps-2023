#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.244"

int main() {

	unsigned int major;
	unsigned int minor;
	unsigned int attrCount;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);
	if(!ctx)
	{
		printf("Wrong IP address! Exiting..\n");
		return 0;
	}

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	iio_context_get_attr(ctx,0,&ctx_name,&ctx_val); 
	printf("ctx attr %d: %s - %s\n" ,0, ctx_name, ctx_val);
	attrCount = iio_context_get_attrs_count(ctx);
	printf("attrs count : %d\n", attrCount);
	for(int i=0; i<attrCount; i++){
		const char *attr_name;
		const char *attr_value;
		iio_context_get_attr(ctx, i, &attr_name, &attr_value);
		printf("Attribute %d : name = %s - value = %s\n", i, attr_name, attr_value);
	}
	printf("\n");

	unsigned int deviceCount = iio_context_get_devices_count(ctx);
	struct iio_device *dev;
	struct iio_channel *chan;

	

	iio_context_destroy(ctx);

	return 0;
}
