#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {

	int n = 10;

	for(int i = 0; i < n; i++){
		printf("Hello Analog Devices student %d \n", i);
		sleep(1);
	}
	return 0;
}
