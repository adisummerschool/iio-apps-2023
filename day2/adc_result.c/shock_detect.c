#include <stdio.h>
#include <iio.h>
#include <string.h>

#define URI "ip:10.76.84.210"

#define RAW2ACCEL	9.8 / 4096
#define THRESH		RAW2ACCEL * 1000

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

double get_accel(struct iio_channel* ch_pos, struct iio_channel* ch_neg)
{
    char buff[50];
    const char* attr = "raw";

    double accel_pos = 0;
    double accel_neg = 0;

    iio_channel_attr_read(ch_pos, attr, buff, 50);
    accel_pos = atoi(buff) * RAW2ACCEL;
    iio_channel_attr_read(ch_neg, attr, buff, 50);
    accel_neg = atoi(buff) * RAW2ACCEL;

    return accel_pos - accel_neg;
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
	float voltage, g, accel, prev_accel;
	char *chan_attr_val;
	struct iio_channel *xpos, *xneg, *ypos, *yneg, *zpos, *zneg; 

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL) {
		printf("Context from URI failed\n");
	}

	struct iio_device *dev = iio_context_find_device(ctx, "ad5592r_s");

	unsigned int del[6] = { 0 };
	unsigned int max_del = 0;

	xpos = iio_device_find_channel(dev, "voltage0", false);
	xneg = iio_device_find_channel(dev, "voltage1", false);
	ypos = iio_device_find_channel(dev, "voltage2", false);
	yneg = iio_device_find_channel(dev, "voltage3", false);
	zpos = iio_device_find_channel(dev, "voltage4", false);
	zneg = iio_device_find_channel(dev, "voltage5", false);

	int i = 0;
	double accel_x, accel_y, accel_z;
	double prev_accel_x, prev_accel_y, prev_accel_z;
	double del_x, del_y, del_z;

	while (1) {
		prev_accel_x = accel_x;
		prev_accel_y = accel_y;
		prev_accel_z = accel_z;
		
		accel_x = get_accel(xpos, xneg);
		accel_y = get_accel(ypos, yneg);
		accel_z = get_accel(zpos, zneg);
		
		del_x = abs(accel_x - prev_accel_x);
		del_y = abs(accel_y - prev_accel_y);
		del_z = abs(accel_z - prev_accel_z);

		if (del_x > THRESH)
			printf("x shock!!!\n");

		if (del_y > THRESH)
			printf("y shock!!!\n");

		if (del_z > THRESH)
			printf("z shock!!!\n");
	}

	iio_context_destroy(ctx);

	return 0;
}
