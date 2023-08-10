#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.158"

int main() {
        
	unsigned int ctx_count;
	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	const struct iio_device *dev;
	const char *name;
	const struct iio_channel *chan;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);
        if(ctx == NULL)
	{
		     printf("Check IP address!");
		     return 0;
	}
	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
  
        ctx_count = iio_context_get_attrs_count(ctx);
	printf("ctx numbers: %d", ctx_count); 

	for (int i=0;i<ctx_count;i++)
	{    
	     	
                iio_context_get_attr(ctx,i,&ctx_name,&ctx_val); 
	        printf("\nctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}
        
        dev = iio_context_get_device(ctx, 0); 
	name = iio_device_get_name(dev);
	unsigned numbers_of_channels = iio_device_get_channels_count(dev);
	printf("name: %s\n", name);
	printf("numbers of channels: %d\n", numbers_of_channels);
	chan = iio_device_find_channel(dev, "voltage0", false);
	char tmp[10];

	for(int j=0;j<4;j++)
	    {       
		    iio_channel_attr_read(chan, "raw", tmp, 10);
                    printf("%s\n", tmp);
	    }

         
	iio_context_destroy(ctx);

	return 0;
}
