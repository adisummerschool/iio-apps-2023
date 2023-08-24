#include <stdio.h>
#include <iio.h>
#include <string.h>

#define URI "ip:10.76.84.239"
#define DEV_NAME "ad5592r_s"
#define SAMPLE_CNT 32

typedef 
        struct {
            uint16_t xpoz;
            uint16_t xneg;
            uint16_t ypoz;
            uint16_t yneg;
            uint16_t zpoz;
            uint16_t zneg;
        }buffer_element;

int main()
{
    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *ch[6];
    struct iio_buffer *buf;

    ctx = iio_create_context_from_uri(URI);
    if (!ctx)
    {
        printf("No context");
        goto err;
    }
    dev = iio_context_find_device(ctx, DEV_NAME);
    if (!dev)
    {
        printf("No device\n");
        goto err;
    }

    ch[0] = iio_device_find_channel(dev, "voltage0", false);
    ch[1] = iio_device_find_channel(dev, "voltage1", false);
    ch[2] = iio_device_find_channel(dev, "voltage2", false);
    ch[3] = iio_device_find_channel(dev, "voltage3", false);
    ch[4] = iio_device_find_channel(dev, "voltage4", false);
    ch[5] = iio_device_find_channel(dev, "voltage5", false);

    for (int i = 0; i < 6; i++)
    { /* Verificare optionala */
        if (!ch[i])
        {
            printf("Channel %d not found", i);
            goto err;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        iio_channel_enable(ch[i]);
    }

    buf = iio_device_create_buffer(dev, SAMPLE_CNT, false);

    if(!buf)
    {
        printf("No buffer\n");
        goto err;
    }

    int bytes_read = iio_buffer_refill(buf);
    printf("%d bytes read from buffer\n\n", bytes_read);

    int i=0;

    for(void* ptr = iio_buffer_start(buf);
	     ptr < iio_buffer_end(buf);
	     ptr += iio_buffer_step(buf))
	{
        // for (int j=0; j<12; j+=2)
        // {printf("%x, %d  ",ptr+j, *(uint16_t*)(ptr+j));
        // }

		// printf("iteration = %d \t mem = %p\n", i, ptr);
		i++;

        buffer_element *buf_el;
        buf_el = ptr;

        printf("%d %d %d %d %d %d",
        buf_el->xpoz,
        buf_el->xneg,
        buf_el->ypoz,
        buf_el->yneg,
        buf_el->zpoz,
        buf_el->zneg
        );
        printf("\n");
        
	}

    iio_context_destroy(ctx);
    return 0;

err:
    iio_context_destroy(ctx);
    return 1;
}