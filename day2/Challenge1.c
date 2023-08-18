/**
 * target output:
 *
 * xpos <raw> <volts> <accel_g>
 * xneg <raw> <volts> <accel_g>
 *
 * ypos <raw> <volts> <accel_g>
 * yneg <raw> <volts> <accel_g>
 *
 * zpos <raw> <volts> <accel_g>
 * zneg <raw> <volts> <accel_g>
 */

#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.240"

struct channel
{
	char axis[3];
	int raw;
	float volts;
	float accel_g;
};

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

    printf("Channel\t\tRaw\tVolts\tAccel_g\n");
    // Iterate through its channels
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
        char raw[10] = {0};
        iio_channel_attr_read(ch, attr, raw, 10);

        // Convert to volts
        float volts = atoi(raw) * 2.5 / 4095;

        // Convert to accel in g
        float accel_g = (float)atoi(raw) / 4095;
        
        printf("%s\t%s\t%.2f\t%.2f\n", chn_id, raw, volts, accel_g);
    }

    iio_context_destroy(ctx);
    return 0;
}
