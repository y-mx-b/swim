#include "../include/swim.h"

int main(void) {
    WindowListOptions options = {
            .exclude_desktop_elements = true,
            .on_screen_only           = true,
    };

    WindowList window_list = get_window_list(options, NULL);

    for (int i = 0; i < window_list.count; i++) {
        window     *w        = window_list.windows[i];
        CFStringRef cf_title = get_window_title(w);
        char       *title    = cstring_from_CFString(cf_title);
        char       *app_name =
                cstring_from_CFString(get_application_name((get_window_application(w))));
        CGRect frame = get_window_frame(w);

        printf("Window Number: %d\n", i);
        printf("\tApplication Name: %s\n", app_name);
        printf("\tWindow Title: %s\n", title);
        printf("\tWindow ID: %d\n", get_window_id(w));
        printf("\tWindow Position: (%.2f, %.2f)\n", frame.origin.x, frame.origin.y);
        printf("\tWindow Size:\n");
        printf("\t\tHeight: %.2f\n", frame.size.height);
        printf("\t\tWidth: %.2f\n", frame.size.width);

        free(app_name);
        free(title);
        destroy_window(w);
    }
}
