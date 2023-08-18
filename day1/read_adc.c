#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>  // Include for clock()

#define URI "ip:10.76.84.239"
// #define URI "ip:10.76.84.208"

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

    struct iio_device *dev = iio_context_find_device(ctx, "ad5592r_s");
    if (!dev) {
        fprintf(stderr, "Device 'ad5592r_s' not found.\n");
        iio_context_destroy(ctx);
        return -1;
    }

    const char* axis_names[] = {
        "xpoz",
        "xneg",
        "ypoz",
        "yneg",
        "zpoz",
        "zneg"
    };

    int channel_order[] = {1, 3, 5, 0, 2, 4};  // This specifies the order in which channels should be read

    clock_t start_time = clock();  // Start the clock

    for (int i = 0; i < 6; i++) {
        struct iio_channel *ch = iio_device_get_channel(dev, channel_order[i]);

        char attr_val[1024];
        iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
        int raw = atoi(attr_val);

        double volts = (double)raw / 1638.0;
        double acceleration = (double)raw / 4095.0;

        printf("%s %d %.4lf %.4lf\n", axis_names[i], raw, volts, acceleration);
    }

    clock_t end_time = clock();  // End the clock

    iio_context_destroy(ctx);

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to read all channels: %f seconds\n", time_taken);

    return 0;
}
