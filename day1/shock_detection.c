#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>

#define URI "ip:10.76.84.239"
//#define URI "ip:10.76.84.208"

#define SHOCK_THRESHOLD 0.5

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    unsigned int major;
    unsigned int minor;
    char git_tag[8];
    struct iio_context *ctx;

    iio_library_get_version(&major, &minor, git_tag);
    printf("libiio version: %d.%d - %s\n", major, minor, git_tag);

    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL)
    {
        fprintf(stderr, "Failed to create context from URI: %s\n", URI);
        return -1;
    }

    int dev_count = iio_context_get_devices_count(ctx);

    if (dev_count > 0)
    {
        struct iio_device *dev = iio_context_get_device(ctx, 1);

        const char *axis_names[] = {
            "xpoz",
            "xneg",
            "ypoz",
            "yneg",
            "zpoz",
            "zneg"};

        int channel_order[] = {0, 1, 2, 3, 4, 5};

        while (1)
        {
            // clearConsole();

            for (int i = 0; i < 6; i += 2)
            {
                static double last_two_accels[3][2] = {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};

                struct iio_channel *ch_pos = iio_device_get_channel(dev, channel_order[i]);
                char attr_val_pos[1024];
                iio_channel_attr_read(ch_pos, "raw", attr_val_pos, sizeof(attr_val_pos));
                int raw_pos = atoi(attr_val_pos);
                double accel_pos = (double)raw_pos / 4095.0;

                struct iio_channel *ch_neg = iio_device_get_channel(dev, channel_order[i + 1]);
                char attr_val_neg[1024];
                iio_channel_attr_read(ch_neg, "raw", attr_val_neg, sizeof(attr_val_neg));
                int raw_neg = atoi(attr_val_neg);
                double accel_neg = (double)raw_neg / 4095.0;

                double consolidated_accel = accel_pos - accel_neg;

                if (fabs(last_two_accels[i / 2][1] - consolidated_accel) > SHOCK_THRESHOLD ||
                    fabs(last_two_accels[i / 2][0] - consolidated_accel) > SHOCK_THRESHOLD)
                {
                    time_t rawtime;
                    struct tm *timeinfo;
                    char buffer[80];
                    time(&rawtime);
                    timeinfo = localtime(&rawtime);
                    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
                    printf("Shock detected on %s axis at %s!\n", axis_names[i], buffer);
                }

                last_two_accels[i / 2][0] = last_two_accels[i / 2][1];
                last_two_accels[i / 2][1] = consolidated_accel;
            }

            usleep(100000);
        }
    }
    else
    {
        fprintf(stderr, "No devices found.\n");
    }

    iio_context_destroy(ctx);
    return 0;
}
