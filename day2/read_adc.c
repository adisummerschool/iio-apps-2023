#include <stdio.h>
#include <iio.h>
#include <unistd.h>

const char* URI =  "ip:10.76.84.210";
const char* DEVICE_NAME = "ad5592r_s";

const double VOLTS_PER_LSB = 2.5 / (4096);
const int MAX_RAW_VAL = 4095;

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void print_chn_info (struct iio_channel* chn, const char* chn_name);

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

    while (1) {
        clearConsole();

        print_chn_info(xpos, "xpos");
        print_chn_info(xneg, "xneg");
        print_chn_info(ypos, "ypos");
        print_chn_info(yneg, "yneg");
        print_chn_info(zpos, "zpos");
        print_chn_info(zneg, "zneg");

        usleep(500000); 
    }

    

	iio_context_destroy(ctx);
	return 0;
}

void print_chn_info (struct iio_channel* chn, const char* chn_name)
{
    const char* chn_id = iio_channel_get_id(chn);

    char buff[50];
    const char* attr = "raw";
    iio_channel_attr_read(chn, attr, buff, 50);

    int raw_val = atoi(buff);
    double voltage = raw_val * VOLTS_PER_LSB;

    double acceleration = raw_val / MAX_RAW_VAL; 

    printf("%s(id=%s) \t", chn_name, chn_id);
    printf("raw = %d \t", raw_val);
    printf("volts = %.4lf [V] \t", voltage);
    printf("accel = %.4lf m\\s^2", acceleration);
    printf("\n");
}