#include <stdio.h>
#include<unistd.h>

int main() {
int n,i;
	printf("n=:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Character = %d\n" , i );
		sleep(1);
	}
return 0;
}
