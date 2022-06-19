# Swim Documentation

## Overview

Let's take a look at a simple sample application.

First, you must request permissions in order to ensure you have
the required permissions in order to manage windows.

```C
#include "./include/swim.h"

int main(void) {
// check permissions
    if (!request_accessibility_permissions()
        || !request_screen_recording_permissions()) {
        // screen recording is only required on macOS 10.15+ to access window titles
        printf("Missing required permissions!\n");
        return 0;
    }
}
```

Now, let's get a list of the windows currently on-screen.

```C
#include "./include/swim.h"

int main(void) {
    // check permissions
    if (!request_accessibility_permissions()
        || !request_screen_recording_permissions()) {
        // screen recording is only required on macOS 10.15+ to access window titles
        printf("Missing required permissions!\n");
        return 0;
    }

    // get list of windows
    window_list_options options = {
            .exclude_desktop_elements = true,
            .on_screen_only           = true,
    };

    window_list window_list = get_window_list(options, NULL);
}
```

Finally, let's print the titles of every window on-screen!

```C
#include "./include/swim.h"

int main(void) {
    // check permissions
    if (!request_accessibility_permissions()
        || !request_screen_recording_permissions()) {
        // screen recording is only required on macOS 10.15+ to access window titles
        printf("Missing required permissions!\n");
        return 0;
    }

    // get list of windows
    window_list_options options = {
            .exclude_desktop_elements = true,
            .on_screen_only           = true,
    };

    window_list window_list = get_window_list(options, NULL);

    // print all windows titles
    for (int i = 0; i < window_list.count; i++) {
        struct window *w        = window_list.windows[i];

        // get title, convert to C-string
        CFStringRef    cf_title = w->title;
        char          *title    = cstring_from_CFString(cf_title);

        printf("\tWindow %d: %s\n", i, title);

        free(title);
        destroy_window(w);
    }

    free(window_list.windows)
}
```

Simple, right?
