# Swim Documentation

## Overview

Let's take a look at a simple sample application.

First, you must request permissions in order to ensure you have
the required permissions in order to manage windows.

```C
#include "swim.h"

int main(void) {
// check permissions
    if (!request_accessibility_permissions()
        || !request_screen_recording_permissions()) {
        // screen recording is only required on macOS 10.15+
        printf("Missing required permissions!\n");
        return 0;
    }
}
```

Then, let's get a list of the windows currently on-screen.

```C
#include "swim.h"

int main(void) {
    // check permissions
    if (!request_accessibility_permissions()
        || !request_screen_recording_permissions()) {
        // screen recording is only required on macOS 10.15+
        printf("Missing required permissions!\n");
        return 0;
    }

    // get list of windows
    WindowListOptions options = {
        .exclude_desktop_elements = true,
        .on_screen_only = true,
    };
    WindowList window_list = get_window_list(options, NULL);
}
```

Now, let's print the titles of every window on-screen!

```C
#include "swim.h"

int main(void) {
    // check permissions
    if (!request_accessibility_permissions()
        || !request_screen_recording_permissions()) {
        // screen recording is only required on macOS 10.15+
        printf("Missing required permissions!\n");
        return 0;
    }

    // get list of windows
    WindowListOptions options = {
        .exclude_desktop_elements = true,
        .on_screen_only = true,
    };
    WindowList window_list = get_window_list(options, NULL);

    // print all window titles
    for (int i = 0; i < window_list.count; i++) {
        window *w = window_list.windows[i];

        // get title, convert to C-string
        CFStringRef cf_title = get_window_title(w);
        char *title = cstring_from_CFString(cf_title);

        printf("Window %d: %s\n", i, title);

        // free used resources
        free(title);
        destroy_window(w);
    }
    // free used resources
    free(window_list.windows)
}
```

Simple, right?
