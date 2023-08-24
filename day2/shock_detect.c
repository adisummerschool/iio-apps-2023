// 5. Scrieti un program "shock_detect" care asteapta producerea unui soc. In urma socului programul va afisa "<timestamp> - shock detected"

#include <stdio.h>
#include <iio.h>
#include <unistd.h>

const char* URI =  "ip:10.76.84.201";
const char* DEVICE_NAME = "ad5592r_s";

const double VOLTS_PER_LSB = 2.5 / (4096);
const int MAX_RAW_VAL = 4095;


double get_accel(struct iio_channel* ch_pos, struct iio_channel* ch_neg)
{
    char buff[50];
    const char* attr = "raw";

    double accel_pos = 0;
    double accel_neg = 0;

    iio_channel_attr_read(ch_pos, attr, buff, 50);
    accel_pos = atoi(buff) / MAX_RAW_VAL;
    iio_channel_attr_read(ch_neg, attr, buff, 50);
    accel_neg = atoi(buff) / MAX_RAW_VAL;

    return accel_pos - accel_neg;
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

    printf("Start acceleration readings");

    
    while(1)
    {
        double accel_x = get_accel(xpos, xneg);
        double accel_y = get_accel(ypos, yneg);
        double accel_z = get_accel(zpos, zneg);

        printf("X: %lf  Y: %lf Z: %lf", accel_x, accel_y, accel_z);
		sleep(1); // in seconds
    }

	iio_context_destroy(ctx);
	return 0;
}