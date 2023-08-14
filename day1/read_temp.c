#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.215"

const char* DEVICE_NAME = "ad5592r_s";


int main() {
	struct iio_context *ctx;

	ctx = iio_create_context_from_uri(URI);

	// can't find device
	if(!ctx) {
		printf("[ERROR] : Can't create context with provided URI (%s)", URI);
		return 1;
	}

	// READ TEMPERATURES USING XADC
	struct iio_device* dev = iio_context_find_device(ctx, "xadc");

	if (!dev) {
		printf("[ERROR] : Searching for %s but didn't find match\n", DEVICE_NAME);
		return 1;
	}

	printf("\n\n\n");

	struct iio_channel* chn = iio_device_find_channel(dev, "temp0", false);

	const char* chn_name = iio_channel_get_id(chn);

	char buff[50];
	iio_channel_attr_read(chn, "offset", buff, 50);
	int offset = atoi(buff);

	iio_channel_attr_read(chn, "raw", buff, 50);
	int raw = atoi(buff);

	iio_channel_attr_read(chn, "scale", buff, 50);
	int scale = atoi(buff);

    double temperature = ((raw+offset)*scale)/1000; // scale from mili to degrees

	printf("Channel name: %s \n\t offset = %d \n\t raw = %d \n\t scale = %d \n\n\t temperature =  %.2f °C", chn_name, offset, raw, scale, temperature);

	printf("\n\n\n");
	iio_context_destroy(ctx);
	return 0;
}

