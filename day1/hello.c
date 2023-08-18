#include <stdio.h>
#include <unistd.h>

int main() {

	printf("Hello Analog Devices students\n");
	int n;
	printf("Enter a value for n: ");
	scanf("%d",&n);

	for (int i= 0; i<=n; i++){
		printf("Attribute: %d\n", i);

		sleep(1);
	}

	return 0;
}

