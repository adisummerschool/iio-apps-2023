#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.209"

int main() {

	unsigned int ctx_count;
	unsigned int dev_count;

	const char *dev_id;
	const char *dev_name;
	const char *dev_attr;
	const char *chan_id; 
	const char *chan_attr;
	char valoare[10];

	long long adc_chan_nr_poz = 0;
    long long adc_chan_nr_neg = 0;
	double adc_chan_voltage;
	double adc_chan_acceleration;
    double adc_axis_accel;

	char channels[][6] = {"yneg", 
						  "xpoz",
						  "zpoz",
						  "xneg",
						  "zneg",
						  "ypoz"};

    int chan_index[] = {1, 3, 5, 0, 2, 4};

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chan;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	
	ctx_count = iio_context_get_attrs_count(ctx);

	for(int i=0; i<ctx_count; i++){
		iio_context_get_attr(ctx, i, &ctx_name, &ctx_val); 
		printf("ctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}

	printf("\n");
	
	dev = iio_context_get_device(ctx, 1);

	dev_id = iio_device_get_id(dev);
	dev_name = iio_device_get_name(dev); 
	
	printf("%s : %s\n", dev_id, dev_name);
	
	unsigned int chan_cnt = iio_device_get_channels_count(dev);
	printf("%d\n", chan_cnt);


	//for(int i=0; i<chan_cnt; i++){
		chan = iio_device_get_channel(dev, 1); //xpoz
		chan_attr = iio_channel_get_attr(chan, 0);

		iio_channel_attr_read_longlong(chan, chan_attr, &adc_chan_nr_poz);

        chan = iio_device_get_channel(dev, 3); //xneg
        chan_attr = iio_channel_get_attr(chan, 0);

		iio_channel_attr_read_longlong(chan, chan_attr, &adc_chan_nr_neg);

        if(adc_chan_nr_poz == 0) adc_axis_accel = -(double)adc_chan_nr_neg;
        else adc_axis_accel = (double)adc_chan_nr_poz;

		adc_axis_accel = adc_axis_accel / 4096 * 1000;

        printf("X: %.2f\n", adc_axis_accel);

        
        chan = iio_device_get_channel(dev, 5); //ypoz
		chan_attr = iio_channel_get_attr(chan, 0);

		iio_channel_attr_read_longlong(chan, chan_attr, &adc_chan_nr_poz);

        chan = iio_device_get_channel(dev, 0); //yneg
        chan_attr = iio_channel_get_attr(chan, 0);

		iio_channel_attr_read_longlong(chan, chan_attr, &adc_chan_nr_neg);

        if(adc_chan_nr_poz == 0) adc_axis_accel = -(double)adc_chan_nr_neg;
        else adc_axis_accel = (double)adc_chan_nr_poz;

		adc_axis_accel = adc_axis_accel / 4096 * 1000;

        printf("Y: %.2f\n", adc_axis_accel);
        //printf("Z: %.2f\n", adc_axis_accel);
	//}
	
	iio_context_destroy(ctx);

	return 0;
}
