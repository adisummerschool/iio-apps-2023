#include <stdio.h>
#include <unistd.h>

int main() {
	int n;
	printf("Enter the value for n: "); // Prompt the user
	scanf("%d", &n);                   // Read the input into n
	for (int i=0;i<=n;i++)
	{printf("%d\n",i);
	sleep(1);	}
	printf("\n");
	return 0;
}
