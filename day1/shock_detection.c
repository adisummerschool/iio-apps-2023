
// Cod furat de la Andrei Voic


#include <iio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define URI "ip:10.76.84.210"
#define DEVICE_NAME "ad5592r_s"
#define SHOCK_THRESHOLD 500  // shock threshold
#define SAMPLE_CNT 32


void printShockDetected(const char* axis) {
    time_t now;
    char buffer[80];

    time(&now);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&now));

    printf("%s - shock detected on %s axis\n", buffer, axis);
}

int main() {

    unsigned int major;
    unsigned int minor;
    char git_tag[8];
    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *chan[6];
    struct iio_buffer *buff;

    const char* axis_names[] = {"xpoz",
                                "xneg",
                                "ypoz",
                                "yneg",
                                "zpoz",
                                "zneg"};

    double acceleration[6] = {};


    iio_library_get_version(&major, &minor, git_tag);
    printf("libiio version: %d.%d - %s\n", major, minor, git_tag);

    ctx = iio_create_context_from_uri(URI);
    if (!ctx) {
        printf("Failed to create context from URI: %s\n", URI);
        goto err;
    }

    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(!dev) {
        printf("Device not found\n");
        goto err;
    }

    chan[0] = iio_device_find_channel(dev, "voltage0", false);
    chan[1] = iio_device_find_channel(dev, "voltage1", false);
    chan[2] = iio_device_find_channel(dev, "voltage2", false);
    chan[3] = iio_device_find_channel(dev, "voltage3", false);
    chan[4] = iio_device_find_channel(dev, "voltage4", false);
    chan[5] = iio_device_find_channel(dev, "voltage5", false);
    if (!chan[0] || !chan[1] || !chan[2] || !chan[3] || !chan[4] || !chan[5]) {
        printf("Could not find all channels\n");
        goto err;
    }

    int chan_cnt = iio_device_get_channels_count(dev);

    // echivalent cu echo 1 > scan_elements
    for(int i = 0 ; i < chan_cnt; i++) {
        iio_channel_enable(chan[i]);
    }

    buff = iio_device_create_buffer(dev, SAMPLE_CNT, false);
    if(!buff) {
        printf("Buffer not created\n");
        goto err;
    }

    int bytes_read = iio_buffer_refill(buff);
    printf("%d bytes read from buffer\n", bytes_read);

    void *buff_start = iio_buffer_start(buff);
    void *buff_end = iio_buffer_end(buff);
    int buff_step = iio_buffer_step(buff);
    int k = 0;
    
    // for (void *p = buff_start; p < buff_end; p += buff_step) {

    //     printf("%d\t%x\n", ++k, p);

    //     int l = 0;
    //     for (int offset = 0; offset < 2 * chan_cnt; offset += buff_step / chan_cnt) {
    //         uint16_t *sample = p + offset;
    //         printf("voltage%d\t%x\t%4d\n", l++, sample, *sample);
    //     }
    // }

    while (1) {

        iio_buffer_refill(buff);
        
        for (void *p = buff_start; p < buff_end; p += buff_step) {

            system("clear");
            int i = 0;

            for (int offset = 0; offset < 2 * chan_cnt; offset += buff_step / chan_cnt) {
                uint16_t *sample = p + offset;
                
                double voltage = *sample * (2.5 / 4096.0);
                acceleration[i] = *sample / 4096.0;

                printf("%s\t%d\t%.2lf\t%.4lf\n", axis_names[i], *sample, voltage, acceleration[i]);

                i++;
            }  

            printf("%.4f\n", abs(acceleration[0]-acceleration[1]));
            printf("%.4f\n", abs(acceleration[2]-acceleration[3]));
            printf("%.4f\n", abs(acceleration[4]-acceleration[5]));

            if (abs(acceleration[0] - acceleration[1]) > SHOCK_THRESHOLD) {
                    
                    printShockDetected("X");
            }

            if (abs(acceleration[2] - acceleration[3]) > SHOCK_THRESHOLD) {
                    printShockDetected("Y");
            }

            if (abs(acceleration[4] - acceleration[5]) > SHOCK_THRESHOLD) {
                    printShockDetected("Z");
            }
        }

        // for (int i = 0; i < chan_cnt; i++) {
            
            // char attr_val[1024];
            // iio_channel_attr_read(chan[i], "raw", attr_val, sizeof(attr_val));
            // int raw = atoi(attr_val);

            
        // }

        usleep(1000000);
    }
  
    iio_context_destroy(ctx);
    return 0;

err:
    iio_context_destroy(ctx);
    return 1;

}


// #include <iio.h>
// #include <stdio.h>
// #include <string.h>

// #define URI "ip:10.76.84.168"
// #define DEV_NAME "ad5592r_s"
// #define SAMPLE_CNT 32

// typedef	struct {
// 		uint16_t xpoz;
// 		uint16_t xneg;
// 		uint16_t ypoz;
// 		uint16_t yneg;
// 		uint16_t zpoz;
// 		uint16_t zneg;

// } buffer_element;

// int main() {
// 	struct iio_context *ctx;
// 	struct iio_device *dev;
// 	struct iio_channel *ch[6];
// 	struct iio_buffer *buf;

// 	ctx = iio_create_context_from_uri(URI);
// 	if(!ctx) {
// 		printf("No context\n");
// 		goto err;
// 	}

// 	dev = iio_context_find_device(ctx,DEV_NAME);
// 	if(!dev) {
// 		printf("No device\n");
// 		goto err;
// 	}

// 	ch[0] = iio_device_find_channel(dev, "voltage0", false);
// 	ch[1] = iio_device_find_channel(dev, "voltage1", false);
// 	ch[2] = iio_device_find_channel(dev, "voltage2", false);
// 	ch[3] = iio_device_find_channel(dev, "voltage3", false);
// 	ch[4] = iio_device_find_channel(dev, "voltage4", false);
// 	ch[5] = iio_device_find_channel(dev, "voltage5", false);

// 	for(int i=0;i < 6;i++) { /* Verificare optionala */
// 		if(!ch[i]) {
// 			printf("Channel %d not found\n", i );
// 			goto err;
// 		}
// 	}

// 	for(int i = 0; i < 6;i++ ) {
// 		iio_channel_enable(ch[i]);
// 	}

// 	buf = iio_device_create_buffer(dev, SAMPLE_CNT, false);
// 	if(!buf)  {
// 		printf("No buffer\n");
// 		goto err;
// 	}

// 	int bytes_read = iio_buffer_refill(buf);
// 	printf("%d bytes read from buffer", bytes_read);

// 	int i =0;

// 	int x,y,z;
// 	int xprev,yprev,zprev;

// 	for(void* ptr = iio_buffer_start(buf);
// 	     ptr < iio_buffer_end(buf);
// 	     ptr += iio_buffer_step(buf))
// 	{
// 		printf("iteration = %d \t mem = %p \t data = ", i, ptr);

// 		/* iteratie prin memorie
// 		 for(int j=0;j<6; j++) { // read samples
// 			void* crnt_addr = ptr + j * sizeof(uint16_t);
// 			uint16_t val = *(uint16_t*)(crnt_addr);
// 			printf(" val = %d", val);
// 		}*/

// 		/* hardcodare xpoz,ypoz,etc
// 		uint16_t xpoz = *(uint16_t*) (ptr + 0 * sizeof(uint16_t));
// 		uint16_t xneg = *(uint16_t*) (ptr + 1 * sizeof(uint16_t));
// 		uint16_t ypoz = *(uint16_t*) (ptr + 2 * sizeof(uint16_t));
// 		uint16_t yneg = *(uint16_t*) (ptr + 3 * sizeof(uint16_t));
// 		uint16_t zpoz = *(uint16_t*) (ptr + 4 * sizeof(uint16_t));
// 		uint16_t zneg = *(uint16_t*) (ptr + 5 * sizeof(uint16_t));

// 		*/

// 		// Varianta "eleganta" cu pointer la structura
// 		buffer_element *buf_el;
// 		buf_el = ptr;

// 		printf("%d %d %d %d %d %d",
// 		       buf_el->xpoz,
// 		       buf_el->xneg,
// 		       buf_el->ypoz,
// 		       buf_el->yneg,
// 		       buf_el->zpoz,
// 		       buf_el->zneg
// 		       );


// 		printf("\n");

// 		i++;
// 		// aici se face detectia shockului in continuare

// 	}

// 	iio_context_destroy(ctx);
// 	return 0;

// err:
// 	iio_context_destroy(ctx);
// 	return 1;

// }
