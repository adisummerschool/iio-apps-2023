#include <stdio.h>
#include <iio.h>
#include <string.h>

#define URI "ip:10.76.84.240"
#define DEV_NAME "ad5592r_s"
#define NO_OF_CHANNELS 6
#define CHANNEL_PREFIX "voltage"
#define SAMPLE_CNT 32

typedef struct
{
	uint16_t xpos;
	uint16_t xneg;
	uint16_t ypos;
	uint16_t yneg;
	uint16_t zpos;
	uint16_t zneg;
} buffer_element;

void printTableHeader()
{
	system("clear");
	printf("    |              |  x+   |  x-   |  y+   |  y-   |  z+   |  z-   \n");
	printf("idx |     addr     |  ch1  |  ch2  |  ch3  |  ch4  |  ch5  |  ch6  \n");
	printf("----+--------------+-------+-------+-------+-------+-------+-------\n");
}

int main()
{
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *ch[6];
	struct iio_buffer *buf;

	// Get context and device
	ctx = iio_create_context_from_uri(URI);
	if (!ctx)
	{
		printf("No context\n");
		goto err;
	}
	dev = iio_context_find_device(ctx, DEV_NAME);
	if (!dev)
	{
		printf("No device\n");
		goto err;
	}

	for (int i = 0; i < NO_OF_CHANNELS; ++i)
	{
		// Find channel
		char channel_name[9]; // 8 and null terminator
		sprintf(channel_name, "%s%d", CHANNEL_PREFIX, i);
		ch[i] = iio_device_find_channel(dev, channel_name, false);
		if (!ch[i])
		{
			printf("Channel %d not found\n", i);
			goto err;
		}

		// Enable channel
		iio_channel_enable(ch[i]);
	}

	// Create buffer
	buf = iio_device_create_buffer(dev, SAMPLE_CNT, false);
	if (!buf)
	{
		printf("No buffer\n");
		goto err;
	}

	// SAMPLE_CNT * 2 * NO_OF_CHANNELS
	int bytes_read = iio_buffer_refill(buf);
	printf("%d bytes read from buffer\n", bytes_read);

	// Previous values

	int idx = 0;
	printTableHeader();
	for (void *ptr = iio_buffer_start(buf);
		 ptr < iio_buffer_end(buf);
		 ptr += iio_buffer_step(buf))
	{
		// Print start addresses of each sample
		printf("%3d | %lx", idx++, ptr);

		// Get each sample as an integer

		/* VERSION 1
		// for (int offset = 0; offset < 2 * NO_OF_CHANNELS; offset += 2)
		// {
		// 	uint16_t *sample = ptr + offset;
		// 	printf(" | %4d ", *sample);
		// }
		*/

		/* VERSION 2
		// Map channels to axis
		// uint16_t *xpos = ptr + 0;
		// uint16_t *xneg = ptr + 2;
		// uint16_t *ypos = ptr + 4;
		// uint16_t *yneg = ptr + 6;
		// uint16_t *zpos = ptr + 8;
		// uint16_t *zneg = ptr + 10;

		// Print values
		// printf(" | %4d ", *xpos);
		// printf(" | %4d ", *xneg);
		// printf(" | %4d ", *ypos);
		// printf(" | %4d ", *yneg);
		// printf(" | %4d ", *zpos);
		// printf(" | %4d ", *zneg);
		*/

		// VERSION 3
		buffer_element *buf_el = ptr;
		printf(" | %4d ", buf_el->xpos);
		printf(" | %4d ", buf_el->xneg);
		printf(" | %4d ", buf_el->ypos);
		printf(" | %4d ", buf_el->yneg);
		printf(" | %4d ", buf_el->zpos);
		printf(" | %4d ", buf_el->zneg);

		printf("\n");
	}

	iio_context_destroy(ctx);
	return 0;

err:
	iio_context_destroy(ctx);
	return 1;
}
