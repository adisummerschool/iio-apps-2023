#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#define URI "ip:10.76.84.128"
int main() {
	unsigned int ctx_count;
        unsigned int major;
        unsigned int minor;
        char git_tag[8];
        const char *description;
        const char *ctx_name;
        const char *ctx_val;
        
    struct iio_context *ctx; 
       ctx = iio_create_context_from_uri(URI);
    if(ctx == NULL)
        {
                     printf("Check IP address!");
                     return 0;
        }
        description = iio_context_get_description(ctx);
        printf("Description: %s\n" , description);       
	ctx_count = iio_context_get_attrs_count(ctx);
        printf("ctx numbers: %d", ctx_count);    
	    for (int i=0;i<ctx_count;i++)
        {               
		 iio_context_get_attr(ctx,i,&ctx_name,&ctx_val);
                printf("\nctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);   
		     }
  
       iio_context_destroy(ctx);
    return 0;
}