#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.239"

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
    for (int i = 0; i < dev_count; i++) {
        struct iio_device *dev = iio_context_get_device(ctx, i);
        const char *dev_name = iio_device_get_name(dev);

        if (dev_name && strcmp(dev_name, "ad5592r_s") == 0) {
            printf("Device %d: %s\n", i, dev_name);

            int ch_count = iio_device_get_channels_count(dev);
            for (int j = 0; j < ch_count; j++) {
                struct iio_channel *ch = iio_device_get_channel(dev, j);
                const char *ch_id = iio_channel_get_id(ch); // Get channel ID

                for (int value = 1; value <= 5; value++) {
                    char attr_val[1024];
                    snprintf(attr_val, sizeof(attr_val), "%d", value);
                    iio_channel_attr_write(ch, "raw", attr_val);
                    printf("  Channel %d: Name: %s, ID: %s - Written value: %s\n", j, iio_channel_get_name(ch), ch_id ? ch_id : "(null)", attr_val);
                    sleep(1); // Wait for 1 second
                }
            }
        }
    }

    iio_context_destroy(ctx);

    return 0;
}