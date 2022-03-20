#include "../include/swim.h"
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <stdbool.h>
// #include <ApplicationServices/ApplicationServices.h>
// #include <AvailabilityMacros.h>

WindowList get_window_list(WindowListOptions options, window *w) {
    // set options
    CGWindowListOption cf_options =
            (kCGWindowListOptionAll * options.all)
            | (kCGWindowListOptionOnScreenOnly * options.on_screen_only)
            | (kCGWindowListExcludeDesktopElements * options.exclude_desktop_elements)
            | (kCGWindowListOptionIncludingWindow * options.including_window)
            | (kCGWindowListOptionOnScreenAboveWindow * options.above_window)
            | (kCGWindowListOptionOnScreenBelowWindow * options.below_window);

    // set relative window_count
    CGWindowID relative_window = kCGNullWindowID;
    if (w != NULL) { relative_window = get_window_id(w); }

    // get window information
    CFArrayRef cf_window_dicts =
            CGWindowListCopyWindowInfo(cf_options, relative_window);
    CFIndex window_count = CFArrayGetCount(cf_window_dicts);

    WindowList window_list = {
            .count    = 0,
            .capacity = window_count,
            .windows  = malloc(sizeof(pointer_t) * window_count),
    };

    int counter = 0;
    for (int i = 0; i < window_count; i++) {
        CFDictionaryRef cf_window_dict = CFArrayGetValueAtIndex(cf_window_dicts, i);
        window         *new_w          = window_from_CFDictionary(cf_window_dict);

        // only append if window is valid
        if (new_w != NULL) {
            window_list.windows[counter] = new_w;
            counter += 1;
        }
    }
    window_list.count = counter;

    CFRelease(cf_window_dicts);

    return window_list;
}

// TODO implment this
void set_window_frame(window *window, CGRect new_frame) { }
