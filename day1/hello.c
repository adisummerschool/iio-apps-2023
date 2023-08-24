#include <stdio.h>
#include <unistd.h>

int main() {
	int n;
	n = 20;
	for(int i=1; i<=n; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}