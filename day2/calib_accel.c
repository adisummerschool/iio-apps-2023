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
        struct iio_device *dev = iio_context_get_device(ctx, 0);

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
        bool ok [] = {0, 0, 0, 0, 0, 0};


        

            struct iio_channel *ch;
            char attr_val[1024];
            int raw;
            
            ch = iio_device_get_channel(dev, channel_order[0]); // xpoz
            iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
            raw = atoi(attr_val);
             printf("xpoz : %d \n",raw);
            if(raw > 100 ) printf("Move the 1st POT to left.");
            else ok[3] = 1;

            ch = iio_device_get_channel(dev, channel_order[1]); // xneg
            iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
            raw = atoi(attr_val);
            printf("\nxneg : %d \n",raw);
            if(raw > 100 ) printf("Move the 1st POT to right.");
            else ok[0] = 1;

            ch = iio_device_get_channel(dev, channel_order[2]); // ypoz
            iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
            raw = atoi(attr_val);
            printf("\nypoz : %d \n",raw);
            if(raw > 100 ) printf("Move the 2nd POT to left.");
            else ok[4] = 1;

            ch = iio_device_get_channel(dev, channel_order[3]); // yneg
            iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
            raw = atoi(attr_val);
            printf("\nyneg : %d \n",raw);
            if(raw > 100 ) printf("Move the 2nd POT to right.");
            else ok[1] = 1;

            ch = iio_device_get_channel(dev, channel_order[4]); // zpoz
            iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
            raw = atoi(attr_val);
            printf("\nzpoz : %d \n",raw);
            if(raw < 4000) printf("Move the 3rd POT to left.");
            else ok[5] = 1;

            ch = iio_device_get_channel(dev, channel_order[5]); // zneg
            iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
            raw = atoi(attr_val);
            printf("\nzneg : %d \n",raw);
            if(raw > 100 ) printf("Move the 3rd POT to right.");
            else ok[2] = 1;

            int i = 0, sw = 1;
            while( i < 6 && sw == 1)
                {
                    if(ok[i] == 0 ) sw = 0;
                    i++;
                }
            if(sw == 1) {
                printf("Calibrated!");
                
            }

        
        
    } else {
        fprintf(stderr, "No devices found.\n");
    }

    iio_context_destroy(ctx);
    return 0;
}
