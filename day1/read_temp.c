//READ_TEMP
#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.128"

int main() {
    struct iio_context *ctx;

    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to create context from URI: %s\n", URI);
        return -1;
    }

    int dev_count = iio_context_get_devices_count(ctx);
    for (int i = 0; i < dev_count; i++) {
        struct iio_device *dev = iio_context_get_device(ctx, i);
        const char *dev_name = iio_device_get_name(dev);

        if (dev_name && strcmp(dev_name, "xadc") == 0) {
            int ch_count = iio_device_get_channels_count(dev);
            for (int j = 0; j < ch_count; j++) {
                struct iio_channel *ch = iio_device_get_channel(dev, j);

                if (strcmp(iio_channel_get_id(ch), "temp0") == 0) {
                    long long raw, offset;
                    double scale;

                    iio_channel_attr_read_longlong(ch, "raw", &raw);
                    iio_channel_attr_read_longlong(ch, "offset", &offset);
                    iio_channel_attr_read_double(ch, "scale", &scale);

                    double temp = (raw + offset) * scale;
                    printf("Temperature: %.2f\n", temp);
                }
            }
        }
    }

    iio_context_destroy(ctx);
    return 0;
}
