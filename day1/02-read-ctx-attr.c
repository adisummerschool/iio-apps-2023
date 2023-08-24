#include <stdio.h>
#include <iio.h>
#include <unistd.h>


#define URI "ip:10.76.84.153"

const char* DEVICE_NAME = "ad5592r_s";


int main() {
	struct iio_context *ctx;
    const char *ctx_name;
	const char *ctx_val;

	ctx = iio_create_context_from_uri(URI);

	if(!ctx) {
		printf("[ERROR] : Can't create context with provided URI: %s", URI);
		return 1;
	}

	int attrs_count = iio_context_get_attrs_count(ctx);
	printf("IIO context has %d attributes:\n", attrs_count);

	// 2. Read al context attributes
	for (int i=0; i < attrs_count; i++) {
		iio_context_get_attr(ctx,i,&ctx_name,&ctx_val); 
		printf("\tctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}


	iio_context_destroy(ctx);
	return 0;
}

