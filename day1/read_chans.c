#include <stdio.h>
#include<stdlib.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>

#define URI "ip:10.76.84.208"

int main (){

    unsigned int major;
	unsigned int minor;
	char git_tag[8];
    const char *description;
    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *channel0;
    struct iio_channel *channel1; 
    struct iio_channel *channel2;
    struct iio_channel *channel3;
    struct iio_channel *channel4;
    struct iio_channel *channel5;

    iio_library_get_version(&major, &minor, git_tag);
    printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

    ctx = iio_create_context_from_uri(URI); // (1) imi obtin contextul
    

	description = iio_context_get_description(ctx); // scrie numele 
	printf("Description: %s\n" , description);

	if (ctx == NULL){
		printf("The board is not available!\n");
		return 1;
    }

    dev = iio_context_find_device(ctx, "ad5592r_s"); // (2) caut device-ul 

    // in cd /sys/bus/iio/devices in iio:devices gasesc nume devices si trebuie sa fie ad5592r_s
    channel0 = iio_device_find_channel(dev, "voltage0", false); // (3) caut un atribut care are numele voltage(in device-ul ad5592r am mai multe atribute : l
    //label, raw, etc )  .. am false deoarece citesc 
    channel1 = iio_device_find_channel(dev, "voltage1", false);
    channel2 = iio_device_find_channel(dev, "voltage2", false);
    channel3 = iio_device_find_channel(dev, "voltage3", false);
    channel4 = iio_device_find_channel(dev, "voltage4", false);
    channel5 = iio_device_find_channel(dev, "voltage5", false);


    char chan0_voltage[50];
    char chan1_voltage[50];
    char chan2_voltage[50];
    char chan3_voltage[50];
    char chan4_voltage[50];
    char chan5_voltage[50];

    while(1){
        system("clear");
        iio_channel_attr_read(channel0,"raw",chan0_voltage,50);
        printf("X poz =  %s , voltage = %lf, acceleratie = %lf\n", chan0_voltage, (atoi(chan0_voltage)*2.5)/4095, (atoi(chan0_voltage)/4095.0));
        iio_channel_attr_read(channel1,"raw",chan1_voltage,50);
        printf("X neg =  %s , voltage = %lf, acceleratie = %lf\n", chan1_voltage,(atoi(chan1_voltage)*2.5)/4095, (atoi(chan1_voltage)/4095.0));
        iio_channel_attr_read(channel2,"raw",chan2_voltage,50);
        printf("X poz =  %s , voltage = %lf, acceleratie = %lf\n", chan0_voltage, (atoi(chan2_voltage)*2.5)/4095, (atoi(chan2_voltage)/4095.0));
        iio_channel_attr_read(channel3,"raw",chan3_voltage,50);
        printf("X poz =  %s , voltage = %lf, acceleratie = %lf\n", chan3_voltage, (atoi(chan3_voltage)*2.5)/4095, (atoi(chan3_voltage)/4095.0));
         iio_channel_attr_read(channel4,"raw",chan0_voltage,50);
        printf("X poz =  %s , voltage = %lf, acceleratie = %lf\n", chan4_voltage, (atoi(chan4_voltage)*2.5)/4095, (atoi(chan4_voltage)/4095.0));
         iio_channel_attr_read(channel5,"raw",chan5_voltage,50);
        printf("X poz =  %s , voltage = %lf, acceleratie = %lf\n", chan5_voltage, (atoi(chan5_voltage)*2.5)/4095, (atoi(chan5_voltage)/4095.0));
        usleep(1);

    }

    

    iio_context_destroy(ctx);

}