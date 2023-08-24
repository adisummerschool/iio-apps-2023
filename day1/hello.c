#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	printf("Hello Analog Devices students\n");

	for (int i = 0; i < 6; i++) {
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}
