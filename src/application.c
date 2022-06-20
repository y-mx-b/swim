#include "../include/swim.h"
#include <ApplicationServices/ApplicationServices.h>
#include <AvailabilityMacros.h>
#include <CoreFoundation/CoreFoundation.h>

struct application *
        _create_application(AXUIElementRef ax_app, pid_t pid, CFStringRef name) {
    struct application *app = (struct application *) malloc(sizeof(struct application));

    app->ax_app = ax_app;
    app->pid    = pid;
    app->name   = name;

    return app;
}

struct application *create_application(pid_t pid, enum error *err) {
    AXUIElementRef ax_app = AXUIElementCreateApplication(pid);

    CFStringRef name;
    AXUIElementCopyAttributeValue(ax_app, kAXTitleAttribute, (CFTypeRef *) &name);
    if (name == NULL) {
        assign_error(err, NO_APPLICATION);
        return NULL;
    }
    name = CFStringCreateCopy(kCFAllocatorDefault, name);

    struct application *app = _create_application(ax_app, pid, name);

    return app;
}

bool applications_equal(const struct application *a1, const struct application *a2) {
    if (a1 == NULL || a2 == NULL) { return false; }

    if (a1->pid == a2->pid
        && CFStringCompare(a1->name, a2->name, 0) == kCFCompareEqualTo) {
        return true;
    }

    return false;
}

// DEINIT
void destroy_application(struct application *app) {
    CFRelease(app->name);
    CFRelease(app->ax_app);
    free(app);
}
