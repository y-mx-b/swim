#include "../include/swim.h"

int main(void) {
    window_list_options options = {
            .on_screen_only = true,
    };
    window_list    window_list    = get_window_list(options, NULL);
    struct window *focused_window = window_list.windows[0];

    CGRect new_frame = {
            .origin =
                    {
                             .x = 0,
                             .y = 0,
                             },
            .size =
                    {
                             .height = 100,
                             .width  = 100,
                             },
    };

    char  *window_title     = cstring_from_CFString(focused_window->title);
    char  *application_name = cstring_from_CFString(focused_window->app->name);
    CGRect frame            = focused_window->frame;

    printf("%s\n", application_name);
    printf("%s\n", window_title);
    printf("Current Position: (%.2f, %.2f)\n", frame.origin.x, frame.origin.y);

    free(window_title);
    free(application_name);

    printf("\n");
    set_window_frame(focused_window, new_frame);
}
