#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.239"
//#define URI "ip:10.76.84.208"

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
    struct iio_context *ctx;

    iio_library_get_version(&major, &minor, git_tag);
    printf("libiio version: %d.%d - %s\n", major, minor, git_tag);

    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to create context from URI: %s\n", URI);
        return -1;
    }

    int dev_count = iio_context_get_devices_count(ctx);

    if (dev_count > 0) {
        struct iio_device *dev = iio_context_get_device(ctx, 0);

        const char* axis_names[] = {
            "xpoz",
            "xneg",
            "ypoz",
            "yneg",
            "zpoz",
            "zneg"
        };

        int channel_order[] = {1, 3, 5, 0, 2, 4};  // This specifies the order in which channels should be read

        while (1) {  // This loop will continue indefinitely
            clearConsole();  // Clear the console

            for (int i = 0; i < 6; i++) {
                struct iio_channel *ch = iio_device_get_channel(dev, channel_order[i]);
                
                char attr_val[1024];
                iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
                int raw = atoi(attr_val);

                double volts = (double)raw / 1638.0;
                double acceleration = (double)raw / 4095.0;

                printf("%s %d %.4lf %.4lf\n", axis_names[i], raw, volts, acceleration);
            }

            usleep(3500000); 
        }
    } else {
        fprintf(stderr, "No devices found.\n");
    }

    iio_context_destroy(ctx);
    return 0;
}
