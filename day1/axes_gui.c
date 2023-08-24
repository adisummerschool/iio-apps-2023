#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <ncurses.h>

//#define URI "ip:10.76.84.208"
#define URI "ip:10.76.84.239"

void display_axes_gui(double *accelerations) {
    int height, width;
    getmaxyx(stdscr, height, width);
    int scale_factor = 20; // Adjust as needed for visualization

    // Clear the screen
    clear();

    // Drawing X negative
    mvprintw(height/2, width/2, "<");
    for (int i = 1; i <= accelerations[1] * scale_factor; i++) {
        mvprintw(height/2, width/2 - i, "-");
    }

    // Drawing X positive
    mvprintw(height/2, width/2 + 1, ">");
    for (int i = 1; i <= accelerations[0] * scale_factor; i++) {
        mvprintw(height/2, width/2 + 1 + i, "-");
    }

    // Drawing Y positive
    mvprintw(height/2 - 1, width/2, "^");
    for (int i = 1; i <= accelerations[2] * scale_factor; i++) {
        mvprintw(height/2 - i, width/2, "|");
    }

    // Drawing Y negative
    mvprintw(height/2 + 1, width/2, "v");
    for (int i = 1; i <= accelerations[3] * scale_factor; i++) {
        mvprintw(height/2 + i, width/2, "|");
    }

    // Drawing Z positive and Z negative in the top left corner
    mvprintw(1, 0, "Z+ = ");
    for (int i = 0; i < accelerations[4] * scale_factor; i++) {
        mvprintw(1, 5 + i, "X");
    }

    mvprintw(2, 0, "Z- = ");
    for (int i = 0; i < accelerations[5] * scale_factor; i++) {
        mvprintw(2, 5 + i, "X");
    }

    // Refresh the screen to show the update
    refresh();
}


int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    unsigned int major;
    unsigned int minor;
    char git_tag[8];
    struct iio_context *ctx;

    iio_library_get_version(&major, &minor, git_tag);
    mvprintw(0, 0, "libiio version: %d.%d - %s", major, minor, git_tag);

    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL) {
        mvprintw(2, 0, "Failed to create context from URI: %s", URI);
        endwin();
        return -1;
    }

    int dev_count = iio_context_get_devices_count(ctx);

    if (dev_count > 0) {
        struct iio_device *dev = iio_context_get_device(ctx, 0);
        double accelerations[6];

        const char* axis_names[] = {
            "xpoz",
            "xneg",
            "ypoz",
            "yneg",
            "zpoz",
            "zneg"
        };

        int channel_order[] = {1, 3, 5, 0, 2, 4};  // This specifies the order in which channels should be read

        int ch;
        timeout(0); // Set getch() to be non-blocking

        while ((ch = getch()) != 'q') {  // Press 'q' to exit the loop and the program
            for (int i = 0; i < 6; i++) {
                struct iio_channel *ch = iio_device_get_channel(dev, channel_order[i]);

                char attr_val[1024];
                iio_channel_attr_read(ch, "raw", attr_val, sizeof(attr_val));
                int raw = atoi(attr_val);

                double volts = (double)raw / 1638.0;
                double acceleration = (double)raw / 4095.0;

                accelerations[i] = acceleration;

                mvprintw(4+i, 0, "%s %d %.4lf %.4lf", axis_names[i], raw, volts, acceleration);
            }

            display_axes_gui(accelerations);
            usleep(100000); // Wait for 100 milliseconds before updating again
        }

    } else {
        mvprintw(4, 0, "No devices found.");
    }

    iio_context_destroy(ctx);

    // Close ncurses
    endwin();
    
    return 0;
}
