#include <stdio.h>
#include <iio.h>

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
	printf("xpoz= <%d> <%fV> <%f>\n", raw[1], voltg[1], acc[1]);
	printf("xneg= <%d> <%fV> <%f>\n", raw[3], voltg[3], acc[3]);
	printf("ypoz= <%d> <%fV> <%f>\n", raw[5], voltg[5], acc[5]);
	printf("yneg= <%d> <%fV> <%f>\n", raw[0], voltg[0], acc[0]);
	printf("zpoz= <%d> <%fV> <%f>\n", raw[4], voltg[4], acc[4]);
	printf("zneg= <%d> <%fV> <%f>\n", raw[2], voltg[2], acc[2]);
	printf("\n");

	return 0;
}