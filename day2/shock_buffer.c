#include <stdio.h>
#include <iio.h>
#include <unistd.h>


const char* URI =  "ip:10.76.84.153";
const char* DEVICE_NAME = "ad5592r_s";
#define  SAMPLE_CNT 32


int main()
{
    struct iio_context* ctx = NULL;
    struct iio_device*  dev_ad5592r = NULL;
    struct iio_channel *ch[6];
    struct iio_buffer *buf;

    ctx = iio_create_context_from_uri(URI);
    if (!ctx) {
        printf("[ERROR] : Can't create context with provided URI: %s", URI);
        return 1;
    }
     
    dev_ad5592r = iio_context_find_device(ctx, DEVICE_NAME);
    if (!dev_ad5592r) {
        printf("[ERROR] : Searching for %s but didn't find match\n", DEVICE_NAME);
        return 1;
    }

    ch[0] = iio_device_find_channel(dev_ad5592r, "voltage0", false);  //xpos
    ch[1] = iio_device_find_channel(dev_ad5592r, "voltage1", false);  //xneg
    ch[2] = iio_device_find_channel(dev_ad5592r, "voltage2", false);  //ypos
    ch[3] = iio_device_find_channel(dev_ad5592r, "voltage3", false);  //yneg
    ch[4] = iio_device_find_channel(dev_ad5592r, "voltage4", false);  //zpos
    ch[5] = iio_device_find_channel(dev_ad5592r, "voltage5", false);  //zneg
    
    //verificare optionala
    for(int i = 0; i<6;i++)
    {
	    if(!ch[i])
	    {
		    printf("Channel %d not found\n", i);
		    goto err;
	    }
    }
    for(int i = 0;i < 6 ;i++)
    {
        iio_channel_enable(ch[i]);
    }
    
    buf = iio_device_create_buffer(dev_ad5592r, SAMPLE_CNT, false);

    if(!buf){
	    printf("No buffer\n");
	    goto err;
    }    
    
    int bytes_read = iio_buffer_refill(buf); //extrag date din /dev/iio/device0
    printf("%d bytes read from buffer", bytes_read);
    printf("\n");
    
    int i = 0;
    int x,y,z;
    int xprev, ypev, zprev;


    for(void* ptr = iio_buffer_start(buf);ptr < iio_buffer_end(buf);ptr += iio_buffer_step(buf))
	{
		printf("iteration = %d \t mem = %p", i, ptr);
		
                printf(" Date");
	      for(void *ptr1 = ptr; ptr1 < ptr + iio_buffer_step(buf); ptr1 = ptr1 + 2)
	      {  
		 uint16_t * ptr2;
                 printf(" %d ", * ptr2);
	      }
              
	      /*uint16_t xpoz = *(uint16_t *) (ptr + 0 * sizeof(uint16_t));
	      uint16_t xneg = *(uint16_t *) (ptr + 0 * sizeof(uint16_t));
	      uint16_t ypoz = *(uint16_t *) (ptr + 0 * sizeof(uint16_t));
	      uint16_t yneg = *(uint16_t *) (ptr + 0 * sizeof(uint16_t));
	      uint16_t zpoz = *(uint16_t *) (ptr + 0 * sizeof(uint16_t));
	      uint16_t zneg = *(uint16_t *) (ptr + 0 * sizeof(uint16_t));
              
	      xprev=x;
              x = xpoz - xneg;

	      yprev = y;
	      y= ypoz - yneg ;

	      zprev = z ;
	      z = zpoz - zneg ;*/

	      printf("\n");
	      i++;

	}
   





   iio_context_destroy(ctx);
   return 0;

err:
   iio_context_destroy(ctx);
   return 0;

}
