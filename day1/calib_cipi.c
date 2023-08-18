#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.239"

void guide_and_calibrate(struct iio_device *dev, const char *axis_name, int channel_index) {
    printf("Place the accelerometer with the %s side facing UP.\n", axis_name);
    printf("Press any key once you're ready...\n");
    getchar();

    struct iio_channel *ch = iio_device_get_channel(dev, channel_index);
    
    char attr_val[1024];
    iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
    int raw = atoi(attr_val);

    printf("Raw value for %s: %d\n", axis_name, raw);

    int ideal_raw = 4095; // The expected value when the accelerometer is laid flat on an axis
    int offset = ideal_raw - raw;

    if (offset > 0) {
        if (axis_name[1] == '+') {
            printf("Move the potentiometer to the right by %d units.\n", offset);
        } else if (axis_name[1] == '-') {
            printf("Move the potentiometer to the left by %d units.\n", offset);
        }
    } else if (offset < 0) {
        if (axis_name[1] == '+') {
            printf("Move the potentiometer to the left by %d units.\n", -offset);
        } else if (axis_name[1] == '-') {
            printf("Move the potentiometer to the right by %d units.\n", -offset);
        }
    } else {
        printf("No adjustment needed for %s.\n", axis_name);
    }

    printf("\n");
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
            "x+",
            "x-",
            "y+",
            "y-",
            "z+",
            "z-"
        };

        int channel_order[] = {1, 3, 5, 0, 2, 4};  // Specifies the order in which channels should be read

        for (int i = 0; i < 6; i++) {
            guide_and_calibrate(dev, axis_names[i], channel_order[i]);
        }
    } else {
        fprintf(stderr, "No devices found.\n");
    }

    iio_context_destroy(ctx);
    return 0;
}
