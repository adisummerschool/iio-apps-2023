#include <stdio.h>
#include <iio.h>
#include <string.h>

#define URI "ip:10.76.84.210"

#define RAW2ACCEL	9.8 / 4096
#define THRESH		RAW2ACCEL * 1000
#define SAMPLE_CNT	32
#define DATA_SIZE	2

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

double get_accel(uint16_t pos, uint16_t neg)
{
    double accel_pos;
    double accel_neg;

    accel_pos = (double)pos * RAW2ACCEL;
    accel_neg = (double)neg * RAW2ACCEL;

    return accel_pos - accel_neg;
}

bool is_shock(double *accel, double *prev_accel, int accel_ind)
{
	return abs(accel[accel_ind] - prev_accel[accel_ind]) > THRESH;
}

void iterate_through_samples(struct iio_buffer *buf, int bytes_read,
			     double *accel, double *prev_accel)
{
	static bool first_iteration = 1;
	uint16_t *start = iio_buffer_start(buf);
	uint16_t *stop = iio_buffer_end(buf);
	ptrdiff_t step = iio_buffer_step(buf);

	for (uint16_t *ptr = start; ptr < stop; ptr += step) {
		// printf("%d : %p \n", j, ptr);

		int chan_num = bytes_read / (SAMPLE_CNT * DATA_SIZE);
		bool pos = 1;
		uint16_t *tmp;
		int accel_ind = 0;

		for (int k = 0; k < chan_num; k++) {
			if (pos) {
				tmp = (ptr + k * DATA_SIZE);
			} else {
				accel[accel_ind] = get_accel(*tmp, *(ptr + k * DATA_SIZE));
				// printf("Accel on %c = %f\n", ('x' + accel_ind), accel[accel_ind]);

				if ((!first_iteration) && is_shock(accel, prev_accel, accel_ind)) {
					printf("Shock on %c!\n", ('x' + accel_ind));
				}

				prev_accel[accel_ind] = accel[accel_ind];
				accel_ind++;
			}

			pos = !pos;
		}
		first_iteration = 0;
	}
}

int main() {

	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	struct iio_context *ctx;
	int ret;
	int ctx_attr_c, dev_c;
	float temp;
	struct iio_channel *ch[6];
	struct iio_buffer *buf;
	double accel[3];
	double prev_accel[3];

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);

	if (!ctx) {
		printf("Context from URI failed\n");
		return 1;
	}

	struct iio_device *dev = iio_context_find_device(ctx, "ad5592r_s");
	if (!dev) {
		printf("No device found!\n");
		return 1;
	}

	for (char c = '0'; c <= '5'; c++) {
		char chan_name[10] = "voltage";
		strncat(chan_name, &c, 1);
		printf("Chan name = %s\n", chan_name);
		ch[c - '0'] = iio_device_find_channel(dev, chan_name, false);

		if (!ch[c - '0']) {
			printf("Channel %c not found\n", c);
			return 1;
		}
	}

	for (int i = 0; i < 6; i++) {
		iio_channel_enable(ch[i]);
	}

	buf = iio_device_create_buffer(dev, SAMPLE_CNT, false);
	if (!buf) {
		printf("Buffer no no \n");
		return 1;
	}

	while (1) {
		int bytes_read = iio_buffer_refill(buf);
		// printf("Bytes read : %d\n", bytes_read);

		iterate_through_samples(buf, bytes_read, accel, prev_accel);
	}

	iio_context_destroy(ctx);
	return 0;
}