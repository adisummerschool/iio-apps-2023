// Scrieti un program "shock_detect" care asteapta producerea unui soc.
// In urma socului programul va afisa "<timestamp> - shock detected"
#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>
#define         URI 	"ip:10.76.84.163"
#define    min_diff 	1000

void timestamp()
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    printf("Shock detected - %s",asctime( localtime(&ltime) ) );
}

int check_shock(struct iio_channel* ch, int prev_acc){
	char curr_val[30];
	const char* attr = "raw";
	char* ptr;
	int curr_acc = 0;
	iio_channel_attr_read(ch, attr, curr_val, 30);
	curr_acc = strtod(curr_val, &ptr);
	// printf("%d , %d \n", curr_acc, prev_acc);
	if (abs(curr_acc - prev_acc) > min_diff){
		timestamp();
	}
	return curr_acc;
}

int main() {
	struct iio_context *ctx;
	struct iio_device *dev;
	int prev_acc[6] = {0, 0, 0, 0, 4095, 0};
	int curr_acc[6] = {0};
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
	struct iio_channel* xPos = iio_device_find_channel(dev, "voltage0", false);
	struct iio_channel* xNeg = iio_device_find_channel(dev, "voltage1", false);
	struct iio_channel* yPos = iio_device_find_channel(dev, "voltage2", false);
	struct iio_channel* yNeg = iio_device_find_channel(dev, "voltage3", false);
	struct iio_channel* zPos = iio_device_find_channel(dev, "voltage4", false);
	struct iio_channel* zNeg = iio_device_find_channel(dev, "voltage5", false);
	
	while(1){
		curr_acc[0] = check_shock(xPos, prev_acc[0]);
		curr_acc[1] = check_shock(xNeg, prev_acc[1]);
		curr_acc[2] = check_shock(yPos, prev_acc[2]);
		curr_acc[3] = check_shock(yNeg, prev_acc[3]);
		curr_acc[4] = check_shock(zPos, prev_acc[4]);
		curr_acc[5] = check_shock(zNeg, prev_acc[5]);

		for(int i = 0; i < 6; ++i) {
			prev_acc[i] = curr_acc[i];
		}
	}
	iio_context_destroy(ctx);
	return 0;
}

