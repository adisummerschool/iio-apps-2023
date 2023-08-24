#include <stdio.h>
#include <iio.h>

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);
	return 0;
}
