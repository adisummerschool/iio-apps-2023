//Challenge 1: Print message when context is not available and quit

#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.201"

int main() {

	struct iio_context *ctx;

	ctx = iio_create_context_from_uri(URI);

	if(!ctx) {
		printf("Eroare!");
		return 0;
	}

	return 0;
}