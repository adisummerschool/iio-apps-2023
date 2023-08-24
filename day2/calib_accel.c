// 4. Scrieti un program "calib_accel" care ne ofera instructiuni pentru calibrarea placii:
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

const char* URI =  "ip:10.76.84.201";
const char* DEVICE_NAME = "ad5592r_s";

const double VOLTS_PER_LSB = 2.5 / (4096);
const int MAX_RAW_VAL = 4095;

const int CALIB_TH = 150; 


int read_raw(struct iio_channel* chn)
{
    char buff[50];
    const char* attr = "raw";

    iio_channel_attr_read(chn, attr, buff, 50);
    return atoi(buff);
}

int main(int argc, char* argv[]) {
    if(argc ==2)
    {
        URI = argv[1];
    }

	struct iio_context* ctx = NULL;
    struct iio_device*  dev_ad5592r = NULL;

    struct iio_channel* xpos = NULL;
    struct iio_channel* xneg = NULL;
    struct iio_channel* ypos = NULL;
    struct iio_channel* yneg = NULL;
    struct iio_channel* zpos = NULL;
    struct iio_channel* zneg = NULL;


	ctx = iio_create_context_from_uri(URI);
	if(!ctx) {
		printf("[ERROR] : Can't create context with provided URI: %s", URI);
		return 1;
	}

    dev_ad5592r = iio_context_find_device(ctx, DEVICE_NAME);
	if (!dev_ad5592r) {
		printf("[ERROR] : Searching for %s but didn't find match\n", DEVICE_NAME);
		return 1;
	}

    xpos = iio_device_find_channel(dev_ad5592r, "voltage0", false);
    xneg = iio_device_find_channel(dev_ad5592r, "voltage1", false);
    ypos = iio_device_find_channel(dev_ad5592r, "voltage2", false);
    yneg = iio_device_find_channel(dev_ad5592r, "voltage3", false);
    zpos = iio_device_find_channel(dev_ad5592r, "voltage4", false);
    zneg = iio_device_find_channel(dev_ad5592r, "voltage5", false);

    if (!xpos || !xneg || !ypos || !yneg || !zpos || !zneg) 
    {
		printf("[ERROR] : Coultn't find all channels");
        return 1;
    }

    bool isCalib = false;
    bool xCalib = false;
    bool yCalib = false;
    bool zCalib = false;

    const char* pot1_msg = NULL;
    const char* pot2_msg = NULL;
    const char* pot3_msg = NULL;


    printf("Adjust the potentiometers according to instructions:\n");
    do {
        int xpos_raw = read_raw(xpos);
        int xneg_raw = read_raw(xneg);
        int ypos_raw = read_raw(ypos);
        int yneg_raw = read_raw(yneg);
        int zpos_raw = read_raw(zpos);
        int zneg_raw = read_raw(zneg);

        xCalib = (xpos_raw < CALIB_TH) && (xneg_raw < CALIB_TH);
        yCalib = (ypos_raw < CALIB_TH) && (yneg_raw < CALIB_TH);
        zCalib = (zpos_raw > (MAX_RAW_VAL - CALIB_TH)) && (zneg_raw < CALIB_TH);

        isCalib = xCalib && yCalib && zCalib;

        // printf("xpos = %d, xneg = %d, ");

        if (xCalib) {
            pot1_msg = "centered";
        } else {
            pot1_msg = (xpos_raw > CALIB_TH) ? "counter-clockwise" : "clockwise";
        }

        if (yCalib) {
            pot2_msg = "centered";
        } else {
            pot2_msg = (ypos_raw > CALIB_TH) ? "counter-clockwise" :  "clockwise";
        }

        if (zCalib) {
            pot3_msg = "centered";
        } else {
            pot3_msg = (zneg_raw > CALIB_TH) ? "counter-clockwise" :  "clockwise";
        }

        if(isCalib) 
        {
            printf("Calibrated !");
        } else 
        {
            printf("\rPOT1: %s POT2: %s POT3: %s", pot1_msg, pot2_msg, pot3_msg);
        }

		sleep(5); // in seconds
    } while (!isCalib);

	iio_context_destroy(ctx);
	return 0;
}