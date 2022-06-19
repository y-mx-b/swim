#include "../include/swim.h"
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <stdbool.h>
// #include <ApplicationServices/ApplicationServices.h>
// #include <AvailabilityMacros.h>

window_list
        get_window_list(window_list_options options, struct window *w, enum error *err) {
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
    if (w != NULL) { relative_window = w->id; }

    // get window information
    CFArrayRef cf_window_dicts = CGWindowListCopyWindowInfo(cf_options, relative_window);
    CFIndex    window_count    = CFArrayGetCount(cf_window_dicts);

    window_list window_list = {
            .count    = 0,
            .capacity = window_count,
            .windows  = malloc(sizeof(pointer_t) * window_count),
    };

    int counter = 0;
    for (int i = 0; i < window_count; i++) {
        CFDictionaryRef cf_window_dict = CFArrayGetValueAtIndex(cf_window_dicts, i);
        struct window  *new_w          = window_from_CFDictionary(cf_window_dict, NULL);

        // only append if window is valid
        if (new_w != NULL) {
            window_list.windows[counter] = new_w;
            counter += 1;
        }
    }
    window_list.count = counter;

    CFRelease(cf_window_dicts);

    assign_error(err, NONE);
    return window_list;
}

AXError _set_window_size(AXUIElementRef ax_window, CGSize *size) {
    AXValueRef ax_size = AXValueCreate(kAXValueCGSizeType, size);
    AXError    error = AXUIElementSetAttributeValue(ax_window, kAXSizeAttribute, ax_size);
    return error;
}

AXError _set_window_position(AXUIElementRef ax_window, CGPoint *position) {
    AXValueRef ax_position = AXValueCreate(kAXValueCGPointType, position);
    AXError    error =
            AXUIElementSetAttributeValue(ax_window, kAXPositionAttribute, ax_position);
    return error;
}

void set_window_frame(struct window *window, CGRect new_frame, enum error *err) {
    AXUIElementRef ax_window     = window->ax_window;
    AXError        ax_size_error = _set_window_size(ax_window, &new_frame.size);
    AXError        ax_pos_error  = _set_window_position(ax_window, &new_frame.origin);

    if (ax_size_error != kAXErrorSuccess
        && ax_size_error != kAXErrorSuccess) {               // both error
        assign_error(err, error_from_AXError(ax_pos_error)); // last error
    } else if (
            (ax_size_error != kAXErrorSuccess)
            != (ax_pos_error != kAXErrorSuccess)) { // one error
        if (ax_size_error != kAXErrorSuccess) {
            assign_error(err, error_from_AXError(ax_size_error));
        } else {
            assign_error(err, error_from_AXError(ax_pos_error));
        }
    } else { // no error
        assign_error(err, NONE);
    }
}
