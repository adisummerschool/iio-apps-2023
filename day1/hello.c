#include <stdio.h>
#include <unistd.h>

int main() {

	printf("Hello Analog Devices students\n");
	int n = 10;
	for (int i=0;i<=n;i++)
	{
           printf("%d", i);
	   printf("\n");
	   sleep(1);
	}
	return 0;
}
