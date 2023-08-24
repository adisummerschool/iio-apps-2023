// Read all context attributes

#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.201"

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	const struct iio_device *dev;
	const char *attr = "en";
	char dst[8];
	size_t len = 8;

	iio_library_get_version(&major, &minor, git_tag);

	ctx = iio_create_context_from_uri(URI);
	
	dev = iio_context_find_device(ctx, "ad5592r_s");

	int dev_count = iio_context_get_devices_count(ctx);

	if(!ctx){
		printf("ERROR: Context not available");
		return 0;
	}

	for (int i = 0; i < iio_context_get_attrs_count(ctx); i++){ 
		iio_context_get_attr(ctx, i, &ctx_name, &ctx_val);
		printf("Context attributes: %d - %s -> %s \n", i, ctx_name, ctx_val);
	}

	for (int i = 0; i < iio_device_get_attrs_count(dev); i++){ 
		iio_device_attr_read(dev, "en", dst, len);
		printf("Device attributes: %d - %s \n", i, attr);
	}

	for (int i = 0; i < dev_count; i++) {
        	struct iio_device *dev = iio_context_get_device(ctx, i);
        	const char *dev_name = iio_device_get_name(dev);

        	if (dev_name && strcmp(dev_name, "xadc") == 0) {
            		int ch_count = iio_device_get_channels_count(dev);
            		for (int j = 0; j < ch_count; j++) {
               			struct iio_channel *ch = iio_device_get_channel(dev, j);

                		if (strcmp(iio_channel_get_id(ch), "temp0") == 0) {
                    			long long raw, offset;
                    			double scale;

                    			iio_channel_attr_read_longlong(ch, "raw", &raw);
                    			iio_channel_attr_read_longlong(ch, "offset", &offset);
                    			iio_channel_attr_read_double(ch, "scale", &scale);

                   			 double temp = (raw + offset) * scale;
                   			 printf("Temperature: %.2f\n", temp);
                		}
            		}
       		}		
    	}

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	iio_context_destroy(ctx);

	return 0;
}
