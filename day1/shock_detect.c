#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.240"

int main()
{
	// Get the iio context
	struct iio_context *ctx;
	ctx = iio_create_context_from_uri(URI);
	if (ctx == NULL)
	{
		printf("Context couldn't be returned.\nExiting...");
		return -1;
	}

	// Get device (AD5592R)
	const char *deviceName = "ad5592r_s";
	struct iio_device *ad5592r = iio_context_find_device(ctx, "ad5592r_s");
	if (ad5592r == NULL)
	{
		printf("%s not found!\nExiting...", deviceName);
		return -1;
	}
	printf("%s found!\n", deviceName);

	//printf("Channel  Raw\tVolts\tAccel_g\n");
	// Iterate through its channels
	float v[7] = {0};
	int ch_cnt = iio_device_get_channels_count(ad5592r);
	for (int i = 0; i < ch_cnt - 1; ++i)
	{
		// Get channel
		struct iio_channel *ch = iio_device_get_channel(ad5592r, i);
		const char *chn_id = iio_channel_get_id(ch);

		// Get channel's attributes
		int attr_cnt = iio_channel_get_attrs_count(ch);
		if (attr_cnt != 1)
		{
			printf("Channel has %d attributes instead of 1!\nExiting...", attr_cnt);
			return -1;
		}

		// Read raw value
		char *attr = iio_channel_get_attr(ch, 0);
		char dst[10] = {0};
		iio_channel_attr_read(ch, attr, dst, 10);
		//printf("%d\n",atoi(dst));
		float volts = atoi(dst) * 2.5 / 4096; // raw * resolution * max_voltage
		float accel_g = volts / 0.3; // volts / sensitivity

		v[i] = accel_g;

		//printf("%12s\t%s\t%f\t%f\t\n", chn_id, dst, volts, accel_g);
	}

	/*axa_x = v[0] - v[1];
	axa_y = v[2] - v[3];
	axa_z = v[4] - v[5];

	printf("X = %f\n",axa_x);
	printf("Z = %f\n",axa_y);
	printf("Y = %f\n",axa_z);
	*/

	iio_context_destroy(ctx);
	return 0;
}