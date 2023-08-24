// Challenge 1: Scrieti programul C "read_adc" care citeste de la ADC 
//		valorile de raw ale axelor xpoz,xneg si le afiseaza in 
//		urmatorul format (ex): xpoz <raw> <volts> <acceleration>

#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.201"

int main() {

	struct iio_context *ctx;
	struct iio_device *dev;
	const char *channel_name[6] = {"X+", "X-", "Y+", "Y-", "Z+", "Z-"};

	ctx = iio_create_context_from_uri(URI);
	dev = iio_context_find_device(ctx, "ad5592r_s");

	if(!ctx) {
		printf("Eroare!");
		return 0;
	}

	for(int i = 0; i < iio_device_get_channels_count(dev); ++i) {
		char voltage_nr[50];
		sprintf(voltage_nr, "voltage%d", i);
		struct iio_channel* channel = iio_device_find_channel(dev, voltage_nr, false);
		const char* chn_name = iio_channel_get_id(channel);

		printf("\t%s", channel_name[i]);
	
		for(int j = 0; j < iio_channel_get_attrs_count(channel); ++j) {
			const char* crn_attr = iio_channel_get_attr(channel, j);

			char buff[50];
			iio_channel_attr_read(channel, crn_attr, buff, 50);

			double val = (atof(buff))*(2.5/4095); // val for voltage
			double g = (atof(buff))/4095;  // value for acceleration

			printf("\t%s value : %s, voltage : %.4lf [V], "
			     "acceleration :%lf [g]\n", crn_attr, buff, val, g);
		}
	}
	

	iio_context_destroy(ctx);

	return 0;
}
