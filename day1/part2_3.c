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

	unsigned int deviceCount = iio_context_get_devices_count(ctx);
	struct iio_device *dev;
	struct iio_channel *chan;

	for(int i=0; i<deviceCount; i++){
		dev = iio_context_get_device(ctx, i);
		unsigned int devAttrCount = iio_device_get_attrs_count(dev);
		printf("Dev %d:\n", i);
		for(int j=0; j<devAttrCount; j++){
			const char *attrDes = iio_device_get_attr(dev, j);
			printf("	Attr %d : %s\n", j, attrDes);
		}

		unsigned int devChannelCount=iio_device_get_channels_count(dev);
		for(int j=0; j<devChannelCount; j++){
			chan =  iio_device_get_channel(dev, j);
			
			printf("	Channel %d :\n", j);
			unsigned int chanAttrCount = iio_channel_get_attrs_count(chan);
			for(int d=0; d<chanAttrCount; d++){
				const char* chanAttrDes = iio_channel_get_attr(chan, d);
				printf("		Attr %d : %s\n", d, chanAttrDes);
				char ceva[100]={};
				int err = iio_channel_attr_read(chan, "raw", ceva, 100);
				if(err>0)
					printf("			Raw value: %s \n", ceva);
				else{

				}
			}
		}
	}

	iio_context_destroy(ctx);

	return 0;
}
