#include "../include/swim.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

struct window *_create_window(
        struct application *app, AXUIElementRef ax_window, CGWindowID id, CGRect frame,
        CFStringRef title) {
    struct window *new_window = (struct window *) malloc(sizeof(struct window));

    new_window->app       = app;
    new_window->ax_window = ax_window;
    new_window->id        = id;
    new_window->frame     = frame;
    new_window->title     = title;

    return new_window;
}

AXUIElementRef _get_matching_window_AXUIElementRef(
        AXUIElementRef app, CFStringRef window_title, CGRect window_frame) {
    AXUIElementRef ax_window = NULL;

    // get list of application windows
    CFArrayRef ax_windows = NULL;
    AXUIElementCopyAttributeValue(app, kAXWindowsAttribute, (CFTypeRef *) &ax_windows);
    if (ax_windows == NULL) { return NULL; }
    CFIndex count = CFArrayGetCount(ax_windows);
    if (count == 0) {
        CFRelease(ax_windows);
        return NULL;
    }

    bool match_found = false;

    // get window title & frame for comparison
    CFStringRef title;
    CGRect      frame;
    for (int i = 0; i < count; i++) {
        ax_window = CFArrayGetValueAtIndex(ax_windows, i);

        AXValueRef ax_size;
        AXValueRef ax_origin;

        AXUIElementCopyAttributeValue(ax_window, kAXTitleAttribute, (CFTypeRef *) &title);
        AXUIElementCopyAttributeValue(
                ax_window, kAXSizeAttribute, (CFTypeRef *) &ax_size);
        AXUIElementCopyAttributeValue(
                ax_window, kAXPositionAttribute, (CFTypeRef *) &ax_origin);

        AXValueGetValue(ax_size, kAXValueCGSizeType, &frame.size);
        AXValueGetValue(ax_origin, kAXValueCGPointType, &frame.origin);
        CFRelease(ax_size);
        CFRelease(ax_origin);

        // final checks
        if (title != NULL && window_title == NULL) {
            CFRelease(title);
            continue;
        }
        if ((title == NULL && window_title != NULL)
            || CFStringCompare(title, window_title, 0) != kCFCompareEqualTo
            || CGRectEqualToRect(frame, window_frame) == false) {
            continue;
        }

        CFRetain(ax_window);
        match_found = true;
        break;
    }
    CFRelease(ax_windows);

    if (match_found == false) {
        if (title != NULL) { CFRelease(title); }
        return NULL;
    }

    return ax_window;
}

struct window *window_from_CFDictionary(CFDictionaryRef window_dict) {
    struct window *new_window = NULL;

    // check window layer
    // if not on normal level, skip
    CFNumberRef cf_layer = CFDictionaryGetValue(window_dict, kCGWindowLayer);
    int         layer;
    CFNumberGetValue(cf_layer, kCFNumberIntType, &layer);
    if (layer != 0) { return NULL; }

    // get necessary information to acquire AXUIElementRef
    CFNumberRef cf_pid = CFDictionaryGetValue(window_dict, kCGWindowOwnerPID);
    pid_t       pid;
    CFNumberGetValue(cf_pid, kCFNumberIntType, &pid);

    CFStringRef title = CFDictionaryGetValue(window_dict, kCGWindowName);
    if (title != NULL) { title = CFStringCreateCopy(kCFAllocatorDefault, title); }

    CFDictionaryRef cf_frame = CFDictionaryGetValue(window_dict, kCGWindowBounds);
    CGRect          frame;
    CGRectMakeWithDictionaryRepresentation(cf_frame, &frame);
    if (CGSizeEqualToSize(frame.size, (CGSize){0, 0})) {
        if (title != NULL) { CFRelease(title); }
        return NULL;
    }

    struct application *app = create_application(pid);
    if (app == NULL) {
        if (title != NULL) { CFRelease(title); }
        return NULL;
    }

    // get AXUIElementRef
    AXUIElementRef ax_window =
            _get_matching_window_AXUIElementRef(app->ax_app, title, frame);

    // get remaining information
    CFNumberRef cf_id = CFDictionaryGetValue(window_dict, kCGWindowNumber);
    CGWindowID  id;
    CFNumberGetValue(cf_id, kCGWindowIDCFNumberType, &id);

    // final checks
    if (ax_window == NULL) {
        if (title != NULL) { CFRelease(title); }
        return NULL;
    }

    new_window = _create_window(app, ax_window, id, frame, title);

    return new_window;
}

bool windows_equal(struct window *w1, struct window *w2) {
    bool title_equality;
    if (w1->title == NULL && w2->title == NULL) {
        title_equality = true;
    } else if (w1->title == NULL || w2->title == NULL) {
        title_equality = false;
    } else if (CFStringCompare(w1->title, w2->title, 0) == kCFCompareEqualTo) {
        title_equality = true;
    }

    if (applications_equal(w1->app, w2->app) && w1->id == w2->id
        && CGRectEqualToRect(w1->frame, w2->frame) && title_equality) {
        return true;
    }
    return false;
}

// GET WINDOW PROPERTIES
AXUIElementRef get_window_AXUIElementRef(struct window *window) {
    return window->ax_window;
}

struct application *get_window_application(struct window *window) {
    return window->app;
}

CGWindowID get_window_id(struct window *window) {
    return window->id;
}

CFStringRef get_window_title(struct window *window) {
    return window->title;
}

CGRect get_window_frame(struct window *window) {
    return window->frame;
}

// DEINIT
void destroy_window(struct window *window) {
    if (window->app != NULL) { destroy_application(window->app); }
    if (window->ax_window != NULL) { CFRelease(window->ax_window); }
    if (window->title != NULL) { CFRelease(window->title); }
    free(window);
}
