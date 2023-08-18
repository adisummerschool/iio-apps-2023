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


	printf("\n Last part:\n");
	struct iio_device *devADC;
	struct iio_device *chanADC;
	devADC = iio_context_find_device(ctx, "xadc");
	unsigned int devADCChanCount = iio_device_get_channels_count(devADC);
	for (int i = 0; i < devADCChanCount; i++)
	{
		chanADC = iio_device_get_channel(devADC, i);
		//(raw + offset) * scale

		unsigned int chanADCAttrCount = iio_channel_get_attrs_count(chanADC);

		for(int d=0; d<chanADCAttrCount; d++){
			const char* chanAttrDes = iio_channel_get_attr(chanADC, d);

			char *raw = (char*)malloc(10*sizeof(char));
			char *scale = (char*)malloc(10*sizeof(char));
			char *offset = (char*)malloc(10*sizeof(char));
			
			iio_channel_attr_read(chanADC, "offset", offset, 100);
			iio_channel_attr_read(chanADC, "raw", raw, 100);
			iio_channel_attr_read(chanADC, "scale", scale, 100);

			int offs = atoi(offset);
			if(offs)
			{
				int sc = atoi(scale);
				int rw = atoi(raw);
				printf("Offset : %d , raw : %d, scale : %d\n", offs, rw, sc);
				int rez = (rw + offs)*sc;
				printf("Rezultat = %d\n", rez);
				
				goto end;
			}
		}
	}
	end: 

	iio_context_destroy(ctx);

	return 0;
}
