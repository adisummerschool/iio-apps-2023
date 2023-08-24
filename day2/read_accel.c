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

    if (dev_count > 0) {
        struct iio_device *dev = iio_context_get_device(ctx, 1);

        const char* axis_names[] = {
            "xpoz",
            "xneg",
            "ypoz",
            "yneg",
            "zpoz",
            "zneg"
        };



        int channel_order [] = { 1 , 3, 5, 0, 2, 4};
        int ch_count = iio_device_get_channels_count(dev);

        // Display channels in the specified order
        for (int j = 0; j < 6; j=j+2) {
            if (j < ch_count) {
                struct iio_channel *chp = iio_device_get_channel(dev, channel_order[j]);
                struct iio_channel *chn = iio_device_get_channel(dev, channel_order[j+1]);
            
                char attr_val1[1024];
                iio_channel_attr_read(chp, "raw", attr_val1, sizeof(attr_val1));
                int raw1 = atoi(attr_val1);

                char attr_val2[1024];
                iio_channel_attr_read(chn, "raw", attr_val2, sizeof(attr_val2));
                int raw2 = atoi(attr_val2);

                double acceleration = (double)(raw1 - raw2)/ 4095.0;

                if( j == 0 )
                    printf("X :  %.4lf\n", acceleration);
                if ( j == 2 )
                    printf("Y :  %.4lf\n", acceleration);
                if ( j == 4 )
                    printf("Z :  %.4lf\n", acceleration);
            } else {
                printf("%s Not Available\n", axis_names[j]);
            }
        }
    } else {
        fprintf(stderr, "No devices found.\n");
    }

    iio_context_destroy(ctx);
    return 0;
}
