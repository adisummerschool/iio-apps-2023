#include<stdio.h>
#include<stdlib.h>
#include<iio.h>
#include<unistd.h>
#include<time.h>

#define URI 	       "ip:10.76.84.208"
#define DEV_NAME       "ad5592r_s"
#define SAMPLE_CNT     32

typedef struct {
	uint16_t xpoz;
	uint16_t xneg;
	uint16_t ypoz;
	uint16_t yneg;
	uint16_t zpoz;
	uint16_t zneg;
} buffer_element;

int main() {

	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *chn[6];
	struct iio_buffer *buf;

	ctx = iio_create_context_from_uri(URI);

	if (ctx == NULL)
	{
		printf("Cannot connect to the board.\n");
		return 1;
	}

	dev = iio_context_find_device(ctx, DEV_NAME);

	if (!dev) {
		printf("Cannot find the device.\n");
		return 1;
	}

	chn[0] = iio_device_find_channel(dev, "voltage0", false);
	chn[1] = iio_device_find_channel(dev, "voltage1", false);
	chn[2] = iio_device_find_channel(dev, "voltage2", false);
	chn[3] = iio_device_find_channel(dev, "voltage3", false);
	chn[4] = iio_device_find_channel(dev, "voltage4", false);
	chn[5] = iio_device_find_channel(dev, "voltage5", false);

	for (int i = 0; i < 6; i++)
	{
		if (!chn[i])
		{
			printf("Channel %d not found.\n", i);
			return 1;
		}

		iio_channel_enable(chn[i]);
	}

	buf = iio_device_create_buffer(dev, SAMPLE_CNT, false);

	if (!buf)
	{
		printf("Cannot create buffer.\n");
		return 1;
	}

	int byte_read = iio_buffer_refill(buf);
	printf("Number of bytes read = %d\n", byte_read);
	
	int step_size = iio_buffer_step(buf);
	int j = 0;
	int x, y, z;
	int xprev, yprev, zprev;
	
	for (void *i = iio_buffer_start(buf); 
	     i < iio_buffer_end(buf); 
	     i += step_size)
	{
		printf("sample%i @ %x\n", j, i);

		/* for (void *k = i; k < i + step_size; k += 2)
		   {
		   	printf("%d ", * (uint16_t *) k);
		   }

		   printf("\n"); */

		/*uint16_t xpoz = *(uint16_t *) (i + 0 * sizeof(uint16_t));
		uint16_t xneg = *(uint16_t *) (i + 1 * sizeof(uint16_t));
		uint16_t ypoz = *(uint16_t *) (i + 2 * sizeof(uint16_t));
		uint16_t yneg = *(uint16_t *) (i + 3 * sizeof(uint16_t));
		uint16_t zpoz = *(uint16_t *) (i + 4 * sizeof(uint16_t));
		uint16_t zneg = *(uint16_t *) (i + 5 * sizeof(uint16_t));
		xprev = x;
		x = xpoz - xneg;
		yprev = y;
		y = ypoz - yneg;
		zprev = z;
		z = zpoz - zneg;*/

		buffer_element *buf_el;
		buf_el = i;
		printf("%d %d %d %d %d %d\n",
		       buf_el->xpoz,
		       buf_el->xneg,
		       buf_el->ypoz,
		       buf_el->yneg,
		       buf_el->zpoz,
		       buf_el->zneg);
		// shock detection to be implemented
		j++;
	}

	iio_context_destroy(ctx);

	return 0;
}