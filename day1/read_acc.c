#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>
#define URI "ip:10.76.84.128"
int main() {
    struct iio_context *ctx;
    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to create context from URI: %s\n", URI);
        return -1;
    }
    int dev_count = iio_context_get_devices_count(ctx);
    const char *channel_names[] = {
        "voltage0", "voltage1", "voltage2",
        "voltage3", "voltage4", "voltage5"
    };
    const char *axis_names[] = {
        "xpoz", "xneg", "ypoz", "yneg", "zpoz", "zneg"
    };
    while(1){
        usleep(50000);
        system("clear");
    for (int i = 0; i < dev_count; i++) {
        struct iio_device *dev = iio_context_get_device(ctx, i);
        const char *dev_name = iio_device_get_name(dev);
        if (dev_name && strcmp(dev_name, "ad5592r_s") == 0) {
            int ch_count = iio_device_get_channels_count(dev);
            for (int j = 0; j < ch_count; j++) {
                struct iio_channel *ch = iio_device_get_channel(dev, j);
                const char *ch_id = iio_channel_get_id(ch);
                long long raw;
                double acceleration;
                iio_channel_attr_read_longlong(ch, "raw", &raw);
                // Calculate acceleration based on the raw value
                acceleration = (double)raw / 4095.0;
                int axis_index = -1;
                for (int k = 0; k < 6; k++) {
                    if (strcmp(ch_id, channel_names[k]) == 0) {
                        axis_index = k;
                        break;
                    }
                }
                if (axis_index != -1) {
                    printf("%s %.4f\n", axis_names[axis_index], acceleration);
                }
            }
        }
    }
    }
    iio_context_destroy(ctx);
    return 0;
}