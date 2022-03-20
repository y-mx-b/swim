#include "../include/swim.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

struct window {
    application   *app;
    AXUIElementRef ax_window;
    CGWindowID     id;
    // int layer;
    CGRect      frame;
    CFStringRef title;
};


// create new window struct
window *_create_window(
        application *app, AXUIElementRef ax_window, CGWindowID id, CGRect frame,
        CFStringRef title) {
    window *new_window = (window *) malloc(sizeof(window));

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

    CFArrayRef ax_windows = NULL;
    AXUIElementCopyAttributeValue(app, kAXWindowsAttribute, (CFTypeRef *) &ax_windows);
    if (ax_windows == NULL) { return NULL; }
    CFIndex count = CFArrayGetCount(ax_windows);
    if (count == 0) {
        CFRelease(ax_windows);
        return NULL;
    }
    bool match_found = false;

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

        match_found = true;
        break;
    }
    CFRelease(ax_windows);

    if (match_found == false) {
        if (title != NULL) { CFRelease(title); }
        return NULL;
    }

    // TODO figure out a way to return a copy
    return ax_window;
}

// return NULL if fail
window *window_from_CFDictionary(CFDictionaryRef window_dict) {
    window *new_window = NULL;

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

    application *app = create_application(pid);
    if (app == NULL) {
        if (title != NULL) { CFRelease(title); }
        return NULL;
    }

    // get AXUIElementRef
    AXUIElementRef ax_window = _get_matching_window_AXUIElementRef(
            get_application_AXUIElement(app), title, frame);

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

bool windows_equal(window *w1, window *w2) {
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

// Get window properties
AXUIElementRef get_window_AXUIElementRef(window *window) {
    return window->ax_window;
}

application *get_window_application(window *window) {
    return window->app;
}

CGWindowID get_window_id(window *window) {
    return window->id;
}

CFStringRef get_window_title(window *window) {
    return window->title;
}

CGRect get_window_frame(window *window) {
    return window->frame;
}

// deinit
void destroy_window(window *window) {
    if (window->app != NULL) { destroy_application(window->app); }
    // if (window->ax_window != NULL) { CFRelease(window->ax_window); }
    if (window->title != NULL) { CFRelease(window->title); }
    free(window);
}
