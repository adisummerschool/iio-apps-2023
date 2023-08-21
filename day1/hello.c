#include <stdio.h>
#include <unistd.h>

int main() {
	int n = 6;
	int time = 1;

	for(int i = 0; i < n; i++){
		printf("%d\n", i);
		sleep(time);
	}
	return 0;
}
