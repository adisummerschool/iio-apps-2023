#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define DELTA 500

const char* URI =  "ip:10.76.84.153";
const char* DEVICE_NAME = "ad5592r_s";

const double VOLTS_PER_LSB = 2.5 / 4096;  // Simplified the calculation
const int MAX_RAW_VAL = 4095;

int main(int argc, char* argv[]) {
    if (argc == 2) {
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
    if (!ctx) {
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

    if (!xpos || !xneg || !ypos || !yneg || !zpos || !zneg) {
        printf("[ERROR] : Couldn't find all channels");
        return 1;
    }

    printf("Start acceleration readings\n");

    double prev_accel_x = 0;
    double prev_accel_y = 0;
    double prev_accel_z = 0;

    while (1) {
        char buff[50];
        double voltage;

        // Read and calculate the acceleration values for each axis
        iio_channel_attr_read(xpos, "raw", buff, sizeof(buff));
        voltage = atof(buff);
        double accel_x = voltage;

        iio_channel_attr_read(ypos, "raw", buff, sizeof(buff));
        voltage = atof(buff);
        double accel_y = voltage;

        iio_channel_attr_read(zpos, "raw", buff, sizeof(buff));
        voltage = atof(buff);
        double accel_z = voltage;

        // Detect shocks based on changes in acceleration values
        if ((accel_x - prev_accel_x) > DELTA || (accel_y - prev_accel_y) > DELTA || (accel_z - prev_accel_z) > DELTA) {
            printf("Shock detected\n");
        }

        prev_accel_x = accel_x;
        prev_accel_y = accel_y;
        prev_accel_z = accel_z;

        printf("X: %lf  Y: %lf Z: %lf\n", accel_x, accel_y, accel_z);
        sleep(1);
    }

    iio_context_destroy(ctx);
    return 0;
}
