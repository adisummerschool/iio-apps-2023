#include <stdio.h>
#include <iio.h>
#include <unistd.h>


#define URI "ip:10.76.84.153"

const char* DEVICE_NAME = "ad5592r_s";


int main() {
	struct iio_context *ctx;
    const char *ctx_name;
	const char *ctx_val;

	ctx = iio_create_context_from_uri(URI);

	if(!ctx) {
		printf("[ERROR] : Can't create context with provided URI: %s", URI);
		return 1;
	}

    printf("Print all device/channel attributes: \n");

    int num_devices = iio_context_get_devices_count(ctx);
	printf("IIO context has %d devices:\n", num_devices);

	for (int i=0; i < num_devices; i++) {
		struct iio_device* dev = iio_context_get_device(ctx, i);
		const char* dev_id = iio_device_get_id(dev);
		const char* dev_name = iio_device_get_name(dev);

		printf("\n\n\t %s: %s", dev_id, dev_name);

		int chn_count = iio_device_get_channels_count(dev);
		printf("\n\t %d channels found: ", chn_count);
		for(int j=0; j < chn_count; j++) {
			struct iio_channel* chn= iio_device_get_channel(dev, j);

			const char* chn_id = iio_channel_get_id(chn);
			printf("\n\t\t%s", chn_id);

			int attr_count = iio_channel_get_attrs_count(chn);
			for(int k=0; k < attr_count; k++) {
				char buff[50];
				const char* chn_attr = iio_channel_get_attr(chn , k);
				iio_channel_attr_read(chn, chn_attr, buff, 50);

				printf("\n\t\t\tattr%d: %s \t value: %s", k, chn_attr, buff);
			}
		}
	}


    printf("\n\n ============================================ \n\n");
    printf("Print ONLY device/channel attributes form %s: \n", DEVICE_NAME);

	// Read values from voltage channels of ad5592r_s
	// Find device by ID as well as channels

	struct iio_device* dev = iio_context_find_device(ctx, DEVICE_NAME);

	if (!dev) {
		printf("[ERROR] : Searching for %s but didn't find match\n", DEVICE_NAME);
		return 1;
	}

	printf("Device name: %s\n", iio_device_get_name(dev));
	for (int i=0; i < iio_device_get_channels_count(dev); i++) {
    	char str[50];
		sprintf(str, "voltage%d", i);

		struct iio_channel* chn = iio_device_find_channel(dev, str, false);

		const char* chn_id = iio_channel_get_id(chn);

		printf("\tCurrent chanel %s\n", chn_id);

		for(int j=0; j<iio_channel_get_attrs_count(chn); j++) {
			const char* crn_attr = iio_channel_get_attr(chn, j);

			char buff[50];
			iio_channel_attr_read(chn, crn_attr, buff, 50);
			printf("\t\tattr %d: %s value : %s\n", j, crn_attr, buff);
		}
	}

    printf("\n\n ============================================ \n\n");
	
	// Increment raw value 1 step at a time at channel voltage1
	const char* chn_id = "voltage1";
	struct iio_channel* chn = iio_device_find_channel(dev, chn_id, false);
	char crn_raw_val[10];
	for (int i = 0; i< 20; i++) {
		const char* attr = "raw";
		sprintf(crn_raw_val, "%d", i);
		iio_channel_attr_write(chn, attr, crn_raw_val);
		sleep(1); // in seconds

		char buff[50];
		iio_channel_attr_read(chn, attr, buff, 50);
		printf("\nWritting %d to %s", i, attr);

	}

	iio_context_destroy(ctx);
	return 0;
}

