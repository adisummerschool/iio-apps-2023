#include <stdio.h>
#include <unistd.h>
#include <iio.h>

#define NULL        0
#define URI         "ip:10.76.84.156"
#define DEV_NAME    "ad5592r_s"

struct iio_context *ctx;
struct iio_device  *dev;
struct iio_channel *ch[6];

int main() {

    ctx = iio_create_context_from_uri(URI);
    if(ctx == NULL){
            printf("Specified context does not exist\n");
            return -1;
    }
    uint attr_count = iio_context_get_attrs_count(ctx);
    const char *attr_name;
    const char *attr_value;

    dev = iio_context_find_device(ctx, DEV_NAME);
    if(dev == NULL){
        printf("Could not find specified device");
        return -2;
    }


    uint chan_count = iio_device_get_channels_count(dev);
    for(uint i = 0; i < chan_count; i++){
        ch[i] = iio_device_get_channel(dev, i);
        if(ch[i] == NULL){
            printf("Channel %d does not exist", i);
            return -1;
        }
    }

 
    int chan_values[6];
    while(1){
        for(uint i = 0; i < 6; i++){
            char buff[10];
            iio_channel_attr_read(ch[i], "raw", &buff, 10);
            chan_values[i] = atoi(buff);
        }
	
        int x = chan_values[0] - chan_values[1];
        int y = chan_values[2] - chan_values[3];
        int z = chan_values[4] - chan_values[5];
        printf("x axis: %5d\t y axis: %5d\t z axis: %5d\n", x, y , z);
        fflush(stdout);
        usleep(500 * 1000);
    }
        return 0;
}