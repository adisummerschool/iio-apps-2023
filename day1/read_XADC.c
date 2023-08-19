#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.158"

int main() {
    struct iio_context *ctx;

    ctx = iio_create_context_from_uri(URI);

    // Check if context creation was successful
    if (!ctx) {
        printf("[ERROR] : Failed to create context with provided URI (%s)", URI);
        return 1;
    }

    // Find the device
    struct iio_device* dev = iio_context_find_device(ctx, "xadc");
    if (!dev) {
        printf("[ERROR] : Device %s was not found\n", "ad5592r_s");
        iio_context_destroy(ctx);
        return 1;
    }

    printf("\n\n\n");

    // Find the temperature channel
    struct iio_channel* chn = iio_device_find_channel(dev, "temp0", false);
    if (!chn) {
        printf("[ERROR] : Temperature channel not found\n");
        iio_context_destroy(ctx);
        return 1;
    }

    const char* chn_name = iio_channel_get_id(chn);

    char buff[50];
    iio_channel_attr_read(chn, "offset", buff, 50);
    int offset = atoi(buff);

    iio_channel_attr_read(chn, "raw", buff, 50);
    int raw = atoi(buff);

    iio_channel_attr_read(chn, "scale", buff, 50);
    int scale = atoi(buff);

    double temperature = ((raw + offset) * scale) / 1000; // scaling from milli to degrees

    printf("Channel name: %s\n", chn_name);
    printf("\toffset = %d\n", offset);
    printf("\traw = %d\n", raw);
    printf("\tscale = %d\n", scale);
    printf("\ttemperature = %.2f °C\n", temperature);

    printf("\n\n\n");

    // Clean up and exit
    iio_context_destroy(ctx);
    return 0;
}
