#include "../include/swim.h"

int main(void) {
    WindowListOptions options = {
        .on_screen_only = true,
    };
    WindowList window_list = get_window_list(options, NULL);
    window *focused_window = window_list.windows[0];

    CGRect new_frame = {
        .origin = {
            .x = 0,
            .y = 0,
        },
        .size = {
            .height = 100,
            .width = 100,
        },
    };

    char *window_title = cstring_from_CFString(get_window_title(focused_window));
    char *application_name = cstring_from_CFString(get_application_name(get_window_application(focused_window)));
    CGRect frame = get_window_frame(focused_window);

    printf("%s\n", application_name);
    printf("%s\n", window_title);
    printf("Current Position: (%.2f, %.2f)\n", frame.origin.x, frame.origin.y);

    free(window_title);
    free(application_name);

    printf("\n");
    set_window_frame(focused_window, new_frame);
}
