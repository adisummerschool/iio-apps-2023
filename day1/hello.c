#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	printf("Hello Analog Devices students\n");

	if (argc != 2) {
		printf("Please provide a number as the first argument.\n");
        return 1;
	}

	int n = atoi(argv[1]);;

	for(int i=0; i<n; i++) {
		printf("%d\n", i);
		sleep(1); // in seconds
	}

	return 0;
}
