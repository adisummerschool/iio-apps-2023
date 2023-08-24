#include <stdio.h>
#include<stdlib.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define URI "ip:10.76.84.208"
#define DEV_NAME "ad5592r_s"
#define SAMPLE_CNT 32

int main(){

    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *ch[6];
    struct iio_buffer *buf;

ctx = iio_create_context_from_uri(URI);

if(!ctx){
    printf("No context!");
    goto err;
}

dev = iio_context_find_device(ctx,DEV_NAME);
if (!dev){
    printf("No device!");
    goto err;
}

ch[0] = iio_device_find_channel(dev, "voltage0", false);
ch[1] = iio_device_find_channel(dev, "voltage1", false);
ch[2] = iio_device_find_channel(dev, "voltage2", false);
ch[3] = iio_device_find_channel(dev, "voltage3", false);
ch[4] = iio_device_find_channel(dev, "voltage4", false);
ch[5] = iio_device_find_channel(dev, "voltage5", false);

for (int i = 0; i < 6; i++){/*Verificare optionala*/
    if (!ch[i]){
        printf("Channel %d not found\n", i);
        goto err;
    }
}

for (int i = 0; i < 6; i++){
    iio_channel_enable(ch[i]); // echivalenta cu a face echo 1 in scann elements
}

// Creez bufferul

buf = iio_device_create_buffer(dev, SAMPLE_CNT, false); // creez bufferul , false pentru output
// aici datele mi-au intrat in buffer in sys/...
// Aici datele deja imi sunt stocate pe calculator

//Trebuie sa le iau de acolo cu buffer_reffil

if(!buf){
    printf("No buffer!\n");
    goto err;
}

int bytes_read = iio_buffer_refill(buf); // imi zice cati bytes a extras din buffer 

printf("%d read bytes from buffer", bytes_read);

//SAMPLE_CNT * 2 * 6  (2 -> 16/8, 6 canale)
// trebuie ca acesti bytes pe care ii primim sa ii impartim 
//un sample e format din 2 octeti
// noi avem 6 canale 

// Accesare date 

// in buf am o multime de chestii - imi iau doar ceea ce am nevoie
//iio_buffer_start(buf); // de aici in continuare vor fi datele mele -> pointer spre prima locatie unde se afla datele 
                       // pointer la primul sample
//iio_buffer_end(buf); // pointer spre ultima locatie din datele din buffer

//iio_buffer_step - numarul de bytes de la un sample la altul

/*int k = 0;

for (int i = iio_buffer_start(buf); i < iio_buffer_end(buf); i+=iio_buffer_step(buf)){
        printf("%x %d\n", i, k);
        k++;
}
*/

/*int i = 0;
void * = o adresa de memorie
void* ptr  = un pointer (in cazul in care nu stiu ce tip de date am)
//ca sa accesez o zona de memorie din calculator o fac cu 64 de biti

for (void* ptr = iio_buffer_start(buf); ptr < iio_buffer_end(buf); ptr+=iio_buffer_step(buf)){
        printf("iteration %d \t mem = %p\n", i, ptr);
        i++;
}
*/

int i = 0;
int x,y,z;
int xprev, yprev, zprev;


for (void* ptr = iio_buffer_start(buf); ptr < iio_buffer_end(buf); ptr+=iio_buffer_step(buf)){
        printf("iteration %d \t mem = %p\n", i, ptr);
        //for (void* a = ptr; a < ptr + iio_buffer_step(buf); a += 2){ // decapsulare info
          //  printf(" %d", *(uint16_t *)a);                           //dereferentiere

            uint16_t xpoz = *(uint16_t*) (ptr + 0 *sizeof(uint16_t));
            uint16_t xneg = *(uint16_t*) (ptr + 1 *sizeof(uint16_t));
            uint16_t ypoz = *(uint16_t*) (ptr + 2 *sizeof(uint16_t));
            uint16_t yneg = *(uint16_t*) (ptr + 3 *sizeof(uint16_t));
            uint16_t zpoz = *(uint16_t*) (ptr + 4 *sizeof(uint16_t));
            uint16_t zneg = *(uint16_t*) (ptr + 5 *sizeof(uint16_t));

            xprev = x;
            x = xpoz - xneg;

            yprev = y;
            y = ypoz - yneg;

            zprev = z;
            z = zpoz - zneg;
        }
        printf("\n");
        i++;


iio_context_destroy(ctx);
return 0;


err: 
    iio_context_destroy(ctx);
    return 1;




}