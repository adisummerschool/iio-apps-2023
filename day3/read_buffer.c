// 5. Scrieti un program "shock_detect" care asteapta producerea unui soc. In urma socului programul va afisa "<timestamp> - shock detected"

#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

const char* URI =  "ip:10.76.84.210";
const char* DEVICE_NAME = "ad5592r_s";
const int NUM_CHNANNELS = 6;
const int SAMPLE_COUNT = 32;

float THRESHOLD = 1500;

enum CHAN_IDX {
    XPOS = 0, XNEG, YPOS, YNEG, ZPOS, ZNEG,
};

typedef struct {
    uint16_t xpoz;
    uint16_t xneg;
    uint16_t ypoz;
    uint16_t yneg;
    uint16_t zpoz;
    uint16_t zneg;
} buffer_elem;

void clearConsole();
int findShock(buffer_elem* , buffer_elem* );

int main(int argc, char* argv[]) {
    system("clear");
    printf("\n");

    if(argc ==2)
    {
        URI = argv[1];
    }

    if(argc == 3) {
        URI = argv[1];
        THRESHOLD = atof(argv[2]);
    }

	struct iio_context* ctx = NULL;
    struct iio_device*  dev_ad5592r = NULL;
    struct iio_channel* ch[NUM_CHNANNELS];
    struct iio_buffer* buff = NULL;


	ctx = iio_create_context_from_uri(URI);
	if(!ctx) {
		printf("[ERROR] : Can't create context with provided URI: %s", URI);
		goto err;
	}

    dev_ad5592r = iio_context_find_device(ctx, DEVICE_NAME);
	if (!dev_ad5592r) {
		printf("[ERROR] : Searching for %s but didn't find match\n", DEVICE_NAME);
		goto err;
	}

    ch[XPOS] = iio_device_find_channel(dev_ad5592r, "voltage0", false);
    ch[XNEG] = iio_device_find_channel(dev_ad5592r, "voltage1", false);
    ch[YPOS] = iio_device_find_channel(dev_ad5592r, "voltage2", false);
    ch[YNEG] = iio_device_find_channel(dev_ad5592r, "voltage3", false);
    ch[ZPOS] = iio_device_find_channel(dev_ad5592r, "voltage4", false);
    ch[ZNEG] = iio_device_find_channel(dev_ad5592r, "voltage5", false);

    if (!ch[XPOS] || !ch[XNEG] || !ch[YPOS] || !ch[YNEG] || !ch[ZPOS] || !ch[ZNEG]) 
    {
		printf("[ERROR] : Coultn't find all channels");
		goto err;
    }

    // echivalent cu echo 1 > scan_elements
    for(int i = 0 ; i < NUM_CHNANNELS; i++) {
        iio_channel_enable(ch[i]);
    }
    // echo 32 > watermark      echo 32 * 6 * 2 > length
    buff = iio_device_create_buffer(dev_ad5592r, SAMPLE_COUNT, false);

    if (!buff) {
        printf("[ERROR] : Nu buffer associated to %s device", dev_ad5592r);
		goto err;
    }
    // INITIAL VERSION ================
    // fetch data to host pc  ->  cat din /dev/iio:dev.. in variabila buff din prog c
    // int bytes_read = iio_buffer_refill(buff);
    // printf("%d bytes read from buffer\n", bytes_read);
    // printf("sizeofu16 = %d", sizeof(uint16_t));

    // int i =0;
    // uint16_t crnt_samples[6];
    // uint16_t prev_samples[6] = {0};


    // for(void* ptr = iio_buffer_start(buff); 
    //     ptr < iio_buffer_end(buff);
    //     ptr += iio_buffer_step(buff))
    // {
    //     printf("iteration = %d \t mem = %p\n", i, ptr);
    //     i++;

    //     for(int j=0;j<6; j++) {
    //         void* crnt_addr = ptr + j * sizeof(uint16_t);
    //         uint16_t val = *(uint16_t*)(crnt_addr);
    //         crnt_samples[j] = val;

    //         printf("\t value %d = %d \t addr = %p\n", j, crnt_samples[j], crnt_addr);
    //     }
        
    // }



    // SHOCK DETECTION
    buffer_elem* crnt = (buffer_elem*)malloc(sizeof(buffer_elem));
    buffer_elem* prev = (buffer_elem*)malloc(sizeof(buffer_elem));

    bool firstIteration = true;
    while(1) {
        iio_buffer_refill(buff);

        for(void* ptr = iio_buffer_start(buff); 
            ptr < iio_buffer_end(buff);
            ptr += iio_buffer_step(buff)) {

            memcpy(crnt, ptr, sizeof(buffer_elem));

            if(!firstIteration && findShock(crnt, prev)) {
                printf("Shock detected\n");
            } else {
                firstIteration = false;
            }
                
            memcpy(prev, crnt, sizeof(buffer_elem));
        }
    }


	iio_context_destroy(ctx);
	return 0;
err: 
	iio_context_destroy(ctx);
    return 1;
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int findShock(buffer_elem* crnt, buffer_elem* prev)
{
    if(abs(crnt->xpoz - prev->xpoz) > THRESHOLD)
        return 1;
    if(abs(crnt->xneg - prev->xneg) > THRESHOLD)
        return 1;
    if(abs(crnt->ypoz - prev->ypoz) > THRESHOLD)
        return 1;
    if(abs(crnt->yneg - prev->yneg) > THRESHOLD)
        return 1;
    if(abs(crnt->zpoz - prev->zpoz) > THRESHOLD)
        return 1;
    if(abs(crnt->zneg - prev->zneg) > THRESHOLD)
        return 1;
    return 0;
}