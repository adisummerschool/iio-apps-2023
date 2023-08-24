#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.153"

int main() {
	struct iio_context *ctx;

	ctx = iio_create_context_from_uri(URI);
	if(ctx == NULL)
	{
		printf("Error! Context not available! Exiting the program.\n");
		return 0;
	}
	return 0;
}