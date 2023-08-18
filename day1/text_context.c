#include <stdio.h>
#include <iio.h>
#define URI "ip:10.76.84.128"
int main() {
unsigned int major;
unsigned int minor;
char git_tag[8];
const char *description;
const char *ctx_name;
const char *ctx_val;
struct iio_context *ctx;
iio_library_get_version(&major, &minor, git_tag);
printf("libiio version: %d.%d - %s \n", major, minor, git_tag);
ctx = iio_create_context_from_uri(URI); // Message when context is not available and quit
if (ctx == NULL)
{
        printf("ip gresit!\n");
        return 0;
}
description = iio_context_get_description(ctx);
printf("Description: %s\n", description);
iio_context_get_attr(ctx, 0, &ctx_name, &ctx_val);
printf("ctx attr %d: %s - %s\n", 0, ctx_name, ctx_val);
iio_context_destroy(ctx);
return 0;
}