#include <iio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define URI "ip:10.76.84.201"
#define DEV_NAME "ad5592r_s"
#define NR_CHANNEL 6
#define BUFFER_SIZE 32
#define THRESHOLD 600
//#define DEV#define CHANNEL_PREFIX "voltage"

typedef struct{
		uint16_t xpoz;
		uint16_t xneg;
		uint16_t ypoz;
		uint16_t yneg;
		uint16_t zpoz;
		uint16_t zneg;
	} buffer_elements;

int main()
{
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *ch[6];
	struct iio_buffer *buf;


	ctx = iio_create_context_from_uri(URI);
	if(!ctx)
	{
		printf("No context!");
		return 1;
	}
	dev = iio_context_find_device(ctx, DEV_NAME);
	if(!dev)
	{
		printf("No device!");
		return 1;
	}
	
	ch[0] = iio_device_find_channel(dev, "voltage0", false);
	ch[1] = iio_device_find_channel(dev, "voltage1", false);
	ch[2] = iio_device_find_channel(dev, "voltage2", false);
	ch[3] = iio_device_find_channel(dev, "voltage3", false);
	ch[4] = iio_device_find_channel(dev, "voltage4", false);
	ch[5] = iio_device_find_channel(dev, "voltage5", false);

	for(int i=0; i<NR_CHANNEL; i++)
	{
		if(!ch[i])
		{
			printf("Channel %d not found! \n", i);
			goto err;
		}
	}

	for(int i=0; i<NR_CHANNEL; i++)
	{
		iio_channel_enable(ch[i]);
	}	

	buf = iio_device_create_buffer(dev, BUFFER_SIZE, false);
	if(!buf){
		printf("No buffer!\n");
		goto err;
	}

	int bytes_read = iio_buffer_refill(buf);
	
	printf("%d bytes read from buffer\n", bytes_read);
	
	//BUFFER_SIZE*2*NR_CHANNEL

	//for(int i=0; )

	// int start_buf, end_buf;

	// start_buf = iio_buffer_start(buf);
	// end_buf = iio_buffer_end(buf);
	// ptrdiff_t step = iio_buffer_step(buf);
	// int cnt=0;
	
	// for(int i=start_buf; i<end_buf; i+=step)
        // {
	// 	printf("%x %d\n", i, cnt);
	// 	cnt ++;
	// }
	int i=0;
	for(void* ptr = iio_buffer_start(buf);
	     ptr < iio_buffer_end(buf);
	     ptr += iio_buffer_step(buf))
	{
		//printf("iteration = %d \t mem = %p\n", i, ptr);
		i++;

		printf("%3d | %lx", i++, ptr);

	int cnt=0;
	for(int i = 0; i < 2*NR_CHANNEL; i+=2)
	{
		uint16_t *sample = ptr + i;
		printf("  | voltage%d = %4d", cnt, *sample);
		cnt++;
	}

	buffer_elements *buf_el;
	buf_el = ptr;

	printf("\n%d %d %d %d %d %d", buf_el->xpoz
	, buf_el->xneg
	, buf_el->ypoz
	, buf_el->yneg
	, buf_el->zpoz
	, buf_el->zneg);

	int prevXpoz=0, prevXneg=0, prevYpoz=0, prevYneg=0, prevZpoz=0, prevZneg=0;

	while(true)
	{

	if (abs(buf_el->xpoz - prevXpoz) > THRESHOLD ||
	    abs(buf_el->xneg - prevXneg) > THRESHOLD ||
            abs(buf_el->ypoz - prevYpoz) > THRESHOLD ||
            abs(buf_el->yneg - prevYneg) > THRESHOLD ||
            abs(buf_el->zpoz - prevZpoz) > THRESHOLD ||
            abs(buf_el->zneg - prevZneg) > THRESHOLD)
		{
			char buff[20];
			struct tm *sTm;

			time_t now = time(0);
			sTm = gmtime(&now);

			strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
			printf ("%s %s\n", buff, "\nShake detected!");
		}

		prevXpoz = buf_el->xpoz;
		prevXneg = buf_el->xneg;
		prevYpoz = buf_el->ypoz;
		prevYneg = buf_el->yneg;
		prevZpoz = buf_el->zpoz;
		prevZneg = buf_el->zneg;
	} 
		
	printf("\n");	
	}

	//buf_el -> xneg;

	iio_context_destroy(ctx);
	return 0;

	err:
	iio_context_destroy(ctx);
	return 1;
}