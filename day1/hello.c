#include <stdio.h>
#include <unistd.h>

int main() {
	int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("%d\n", i);
		sleep(1);
    }


	printf("Hello Analog Devices students\n");
	return 0;
}
