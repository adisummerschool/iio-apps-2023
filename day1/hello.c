#include <stdio.h>
#include <unistd.h>

#define N 5

int main() {

	printf("Hello Analog Devices students\n");
	
	for(int i = 0; i < N; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}
	
	return 0;
}
