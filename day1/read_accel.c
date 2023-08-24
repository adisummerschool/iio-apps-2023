// Scrieti un program "read_accel", care afiseaza X,Y,Z in bucla
// X: <acceleration> Y:<acceleration> Z:<acceleration>

#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.163"

int read_accel(struct iio_channel* ch_pos, struct iio_channel* ch_neg){

	char buff_pos[30], buff_neg[30];
	const char* attr = "raw";
	char* ptr;
	int accel_pos = 0;
	int accel_neg = 0;

	iio_channel_attr_read(ch_pos, attr, buff_pos, 30);
	accel_pos = strtod(buff_pos, &ptr);
	iio_channel_attr_read(ch_neg, attr, buff_neg, 30);
	accel_neg = strtod(buff_neg, &ptr);

	return accel_pos - accel_neg;
}

int main() {
	struct iio_context *ctx;
	struct iio_device *dev;
	int xAcc, yAcc, zAcc = 0;
	
	ctx = iio_create_context_from_uri(URI);
	if(!ctx){
		printf("ERROR: Context not available");
		return 0;
	}

	dev = iio_context_find_device(ctx, "ad5592r_s");
	if(!dev){
		printf("ERROR: Ad5592r not available");
		return 0;
	}

	struct iio_channel* xPos = iio_device_find_channel(dev, "voltage0", false);
	struct iio_channel* xNeg = iio_device_find_channel(dev, "voltage1", false);
	struct iio_channel* yPos = iio_device_find_channel(dev, "voltage2", false);
	struct iio_channel* yNeg = iio_device_find_channel(dev, "voltage3", false);
	struct iio_channel* zPos = iio_device_find_channel(dev, "voltage4", false);
	struct iio_channel* zNeg = iio_device_find_channel(dev, "voltage5", false);
	
	while(1){
		xAcc = read_accel(xPos, xNeg);
		yAcc = read_accel(yPos, yNeg);
		zAcc = read_accel(zPos, zNeg);

		printf(" X: %d Y: %d Z: %d \r", xAcc, yAcc, zAcc);
	}
	iio_context_destroy(ctx);
	return 0;
}