#include "../include/swim.h"

int main(void) {
    window_list_options options = {
            .exclude_desktop_elements = true,
            .on_screen_only           = true,
    };

    window_list window_list = get_window_list(options, NULL, NULL);

    for (int i = 0; i < window_list.count; i++) {
        struct window *w        = window_list.windows[i];
        CFStringRef    cf_title = w->title;
        char          *title    = cstring_from_CFString(cf_title);
        char          *app_name = cstring_from_CFString(w->app->name);
        CGRect         frame    = w->frame;

        printf("Window Number: %d\n", i);
        printf("\tApplication Name: %s\n", app_name);
        printf("\tWindow Title: %s\n", title);
        printf("\tWindow ID: %d\n", w->id);
        printf("\tWindow Position: (%.2f, %.2f)\n", frame.origin.x, frame.origin.y);
        printf("\tWindow Size:\n");
        printf("\t\tHeight: %.2f\n", frame.size.height);
        printf("\t\tWidth: %.2f\n", frame.size.width);

        free(app_name);
        free(title);
        destroy_window(w);
    }
}
