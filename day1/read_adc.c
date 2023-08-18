#include <stdio.h>
#include <iio.h>
#include <unistd.h>

#define URI "ip:10.76.84.156"

int main() {
unsigned int major;
unsigned int minor;
char git_tag[8];
struct iio_context *ctx;
char* first_str = "ad5592r_s";

iio_library_get_version(&major, &minor, git_tag);
printf("libiio version: %d.%d - %s\n", major, minor, git_tag);
ctx = iio_create_context_from_uri(URI);

// Message when context is not available and quit
if (ctx == NULL)
{
	printf("ip gresit!\n");
	return 0;
}

int dev_count = iio_context_get_devices_count(ctx);

struct iio_device *dev = iio_context_get_device(ctx, 0);
printf("Device %d: %s\n", 0, iio_device_get_name(dev));

int ch_count = iio_device_get_channels_count(dev);
for (int j = 0; j < ch_count; j++)
{
	struct iio_channel *ch = iio_device_get_channel(dev, j);
        // const char *ch_name = iio_channel_get_name(ch);
        // const char *ch_id = iio_channel_get_id(ch);

	// const char *attr_name = iio_channel_get_attr(ch, 0);
        char attr_val[1024];

	iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
	int raw = atoi(attr_val);

	double volts = (double)raw*(2.5/4095);
        double acceleration = (double)raw / 4095.0;

	if(j == 1)
	{
		printf("Xpoz: <%d> <%f> <%f>\n", raw, volts, acceleration);
	}

	if(j == 3)
	{
		printf("Xneg: <%d> <%f> <%f>\n", raw, volts, acceleration);
	}

	if(j == 5)
	{
		printf("Ypoz: <%d> <%f> <%f>\n", raw, volts, acceleration);
	}

	if(j == 0)
	{
		printf("Yneg: <%d> <%f> <%f>\n", raw, volts, acceleration);
	}

	if(j == 2)
	{
		printf("Zpoz: <%d> <%f> <%f>\n", raw, volts, acceleration);
	}

	if(j == 4)
	{
		printf("Zneg: <%d> <%f> <%f>\n", raw, volts,acceleration);
	}
}

iio_context_destroy(ctx);
return 0;
}