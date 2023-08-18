#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.128"

int main() {

	unsigned int major;
	unsigned int minor;
	unsigned int ctx_count;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	struct iio_context *dev;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);

	iio_context_get_attr(ctx,0,&ctx_name,&ctx_val); 
	printf("ctx attr %d: %s - %s\n" ,0, ctx_name, ctx_val);

	dev = iio_context_find_device(ctx,ctx_name);
	printf("Device available:%d, %s",0,ctx_name);

	if(!ctx)
	{
	printf("Context not availbe\n");
	return 0;
	};

	if(dev)
	{
		printf("Device available: %d, %s\n", iio_device_get_id(dev), ctx_name);
	}
	else
	{
		printf("Device not found!\n");
	}
	  description = iio_context_get_description(ctx);
        printf("Description: %s\n" , description);
       ctx_count = iio_context_get_attrs_count(ctx);
        printf("ctx numbers: %d\n", ctx_count);
     for (int i=0;i<ctx_count;i++)
        {       
			//iio_context_get_attr(ctx,i,&ctx_name,&ctx_val);
            printf("\nctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
    }

	iio_context_destroy(ctx);
	
	
	return 0;
}
