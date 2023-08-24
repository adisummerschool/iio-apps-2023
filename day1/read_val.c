// Scrieti programul C "read_val" care citeste de la ADC valorile de raw ale 
// axelor xpoz,xneg si le afiseaza in urmatorul format:
// xpoz <raw> <volts> <acceleration>
// xneg <raw> <volts> <acceleration>
// ypoz <raw> <volts> <acceleration>
// yneg <raw> <volts> <acceleration>
// zpoz <raw> <volts> <acceleration>
// zneg <raw> <volts> <acceleration>

#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.163"

int main() {
	struct iio_context *ctx;
	struct iio_device *dev;
	const char *channel_name[6] = {"X+", "X-", "Y+", "Y-", "Z+", "Z-"};

	ctx = iio_create_context_from_uri(URI);
	if(!ctx){
		printf("ERROR: Context not available");
		return 0;
	}

	dev = iio_context_find_device(ctx, "ad5592r_s");
	if(!dev){
		printf("ERROR: Ad5592r not available");
		return 0;
	}

	for(int i = 0; i < iio_device_get_channels_count(dev); ++i) {
                char voltage_nr[50];
                sprintf(voltage_nr, "voltage%d", i);
                struct iio_channel* channel = iio_device_find_channel(dev, 
							voltage_nr, false);
                const char* chn_name = iio_channel_get_id(channel);
                printf("\tCurrent channel: %s\n", channel_name[i]);

                for(int j = 0; j < iio_channel_get_attrs_count(channel); ++j) {
                        const char* crn_attr = iio_channel_get_attr(channel, j);
                        char buff[50];
                        iio_channel_attr_read(channel, crn_attr, buff, 50);
			double val = (atof(buff))*(2.5/4096);
			double g = (atof(buff))/4096;
			double acc = g*9.8;
                        printf("\t %s Value : %s, Voltage: %.4lf [V], G's :" 
				"%.4lf [g], Acceleration : %.4lf [m*s^-2]\n", 
				crn_attr, buff, val, g, acc);
                }
	}	
	iio_context_destroy(ctx);
	return 0;
}