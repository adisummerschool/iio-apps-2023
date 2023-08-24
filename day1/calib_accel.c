// Scrieti un program "calib_accel" care ne ofera instructiuni pentru calibrarea placii:
// "Place the module on a plane surface"
// <read user input>
// "Adjust the potentiometers according to instructions"
// "POT1: clockwise POT2: counter-clockwise POT3: center" (example)
// "POT1: clockwise POT2: counter-clockwise POT3: center"
// "POT1: clockwise POT2: center POT3: center"
// "POT1: center POT2: center POT3: center"
// "Calibrated !"

#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>

#define URI "ip:10.76.84.163"

double read_accel(struct iio_channel* ch_pos, struct iio_channel* ch_neg){

	char buff_pos[30], buff_neg[30];
	const char* attr = "raw";
	char* ptr;
	double accel_pos = 0;
	double accel_neg = 0;

	iio_channel_attr_read(ch_pos, attr, buff_pos, 30);
	accel_pos = strtod(buff_pos, &ptr);
	iio_channel_attr_read(ch_neg, attr, buff_neg, 30);
	accel_neg = strtod(buff_neg, &ptr);

	return accel_pos - accel_neg;
}

int main() {
	struct iio_context *ctx;
	struct iio_device *dev;
	bool isCalibrated, xCalib, yCalib, zCalib = false;
	int Threshold = 50;
	double xAcc, yAcc, zAcc = 0;
	char* xAdj;
	char* yAdj;
	char* zAdj;

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

	printf("Place the module on a plane surface \n");
	printf("Adjust the potentiometers according to instructions");
	
	while(1){

		xAcc = read_accel(xPos, xNeg);
		yAcc = read_accel(yPos, yNeg);
		zAcc = read_accel(zPos, zNeg);

		if(xAcc > Threshold){
			xAdj = "counterclockwise";
		}
		else if (xAcc < -Threshold){
			xAdj = "clockwise";
		}
		else{
			xAdj = "center";
			xCalib = true;
		}

		if(yAcc > Threshold){
			yAdj = "counterclockwise";
		}
		else if (yAcc < -Threshold){
			yAdj = "clockwise";
		}
		else{
			yAdj = "center";
			yCalib = true;
		}

		if(zAcc > Threshold){
			zAdj = "counterclockwise";
		}
		else if (zAcc < -Threshold){
			zAdj = "clockwise";
		}
		else{
			zAdj = "center";
			zCalib = true;
		}

		printf(" POT1: %s POT2: %s POT3: %s \r", xAdj, yAdj, zAdj);

		isCalibrated = xCalib && yCalib && zCalib;

		if(isCalibrated){
			printf("\n \t Done!");
		}
	}
	iio_context_destroy(ctx);
	return 0;
}