#include <stdio.h>
#include <unistd.h>

int main() {

	int n = 10;
	for(int i=0;i<n;i++)
	{	printf("%d\n",i);
		sleep(1);
	}
	//printf("Hello Analog Devices students\n");
	return 0;
}
