// 5. Scrieti un program "shock_detect" care asteapta producerea unui soc. In urma socului programul va afisa "<timestamp> - shock detected"

#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <math.h>

const char* URI =  "ip:10.76.84.210";
const char* DEVICE_NAME = "ad5592r_s";

const double VOLTS_PER_LSB = 2.5 / (4096);
const int MAX_RAW_VAL = 4095;

const float THRESHOLD = 0.5;

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


float get_accel(struct iio_channel* ch_pos, struct iio_channel* ch_neg)
{
    char buff_pos[50];
    char buff_neg[50];
    const char* attr = "raw";

    float accel_pos = 0;
    float accel_neg = 0;

    iio_channel_attr_read(ch_pos, attr, buff_pos, 50);
    accel_pos = atof(buff_pos) / MAX_RAW_VAL;
    iio_channel_attr_read(ch_neg, attr, buff_neg, 50);
    accel_neg = atof(buff_neg) / MAX_RAW_VAL;

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


    float x_crnt = get_accel(xpos, xneg), 
           x_prev = 0,
           deltaX;
    float y_crnt = get_accel(ypos, yneg),
           y_prev = 0, 
           deltaY;
    float z_crnt = get_accel(zpos, zneg), 
           z_prev = 0,
           deltaZ;
    
    while(1)
    {
        x_prev = x_crnt;
        y_prev = y_crnt;
        z_prev = z_crnt;

        x_crnt = get_accel(xpos, xneg);
        y_crnt = get_accel(ypos, yneg);
        z_crnt = get_accel(zpos, zneg);

        deltaX = fabs(x_crnt - x_prev);
        deltaY = fabs(y_crnt - y_prev);
        deltaZ = fabs(z_crnt - z_prev);

        // clearConsole();
        printf("deltaX = %f \t deltaY = %f \t deltaZ = %f \n", deltaX, deltaY, deltaZ);

        if( deltaX >= THRESHOLD || deltaY >= THRESHOLD || deltaZ >= THRESHOLD)
        {
            printf("Shock detected!\n");
        }
		usleep(500000); 
    }

	iio_context_destroy(ctx);
	return 0;
}

