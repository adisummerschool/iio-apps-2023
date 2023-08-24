#include <stdio.h>
#include <iio.h>
#include <unistd.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
int nr_ctx_attr;
int nr_chan;

#define URI "ip:10.76.84.153"
#define DEVICE_NAME "ad5592r_s"

int main (){

	ctx = iio_create_context_from_uri(URI);
	if(ctx == NULL){
		printf("Error! Context not available! Exiting the program.\n");
		return 0;
	}

	nr_ctx_attr = iio_context_get_attrs_count(ctx);
	printf("Context attributes: %d", nr_ctx_attr);

	for(int i=0;i<nr_ctx_attr;i++)
	{
		const char *name, *value;
		iio_context_get_attr(ctx, i, &name, &value);
		printf("Name: %s , Value: %s \n", name, value);
	}

	printf("\n");
	dev = iio_context_find_device(ctx, DEVICE_NAME);
	if(dev == NULL){
		printf("No device found\n");
		return 0;
	}

	printf("Device: %s : %x\n\n", DEVICE_NAME, dev);
	nr_chan = iio_device_get_channels_count(dev);
	struct iio_channel *chn[nr_chan];

	for(unsigned int i=0; i<nr_chan; i++)
	{
		chn[i] = iio_device_get_channel(dev, i);
		if(!chn[i]){
			printf("Channel not found\n");
			return -1;
		}
	}

        while(1)
        {
                int raw[nr_chan];
	        double voltg[nr_chan];
	        double acc[nr_chan];
	        for(int i=0; i<nr_chan; i++)
	        {
		        char buffer[10];
		        iio_channel_attr_read(chn[i], "raw", buffer, 10);
                        raw[i] = atoi(buffer);
		        voltg[i]=raw[i]*(2.5/4095);
		        acc[i]=voltg[i]/2.5;
	        }

                double x = acc[1]-acc[3];
		double y = acc[5]-acc[0];
                double z = acc[4]-acc[2];
		printf("x= %f\t y= %f\t z= %f\n", x, y, z);
		printf("\n");

		usleep(500000);
        }
	

	return 0;
}