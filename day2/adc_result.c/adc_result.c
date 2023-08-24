#include <stdio.h>
#include <iio.h>
#include <string.h>
#include <unistd.h>


#define URI "ip:10.76.84.210"

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	int ret;
	int ctx_attr_c, dev_c;
	float temp;
	int raw;
	float scale;
	float voltage, g, accel;
	char *chan_attr_val;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL) {
		printf("Context from URI failed\n");
	}

	struct iio_device *dev = iio_context_find_device(ctx, "ad5592r_s");

	printf("Format:\n<channel_name>: <raw> <voltage> <g> <accel>\n");

	char chan_name[10][10] = {"xpos", "xneg", "ypos", "yneg", "zpos", "zneg"};

	while (1) {
		for (char c = '0'; c <= '5'; c++) {
			char chan_id[10] = "voltage";
			strncat(chan_id, &c, 1);

			struct iio_channel *chan = iio_device_find_channel(dev, chan_id, false);

			

			if(!chan) {
				printf("Channel not found\n");
				return -2;
			}

			chan_attr_val = (char *)malloc(15);
			iio_channel_attr_read(chan, "raw", chan_attr_val, 15);
			raw = atoi(chan_attr_val);
			voltage = (float)raw * 2.5 / 4096;
			g = (float)raw / 4096;
			accel = g * 9.8;
			printf("%s (%s): %d %fV %fg %fm/s^2\n", chan_name[c - '0'], chan_id, raw, voltage, g, accel);
			free(chan_attr_val);
		}
		usleep(100000);
		clearConsole();
	}

	iio_context_destroy(ctx);

	return 0;
}
