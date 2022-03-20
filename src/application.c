#include "../include/swim.h"
#include <ApplicationServices/ApplicationServices.h>
#include <AvailabilityMacros.h>
#include <CoreFoundation/CoreFoundation.h>

struct application {
    AXUIElementRef ax_app;
    pid_t          pid;
    CFStringRef    name;
};

// create application
application *_create_application(AXUIElementRef ax_app, pid_t pid, CFStringRef name) {
    application *app = (application *) malloc(sizeof(application));

    app->ax_app = ax_app;
    app->pid    = pid;
    app->name   = name;

    return app;
}
application *create_application(pid_t pid) {
    AXUIElementRef ax_app = AXUIElementCreateApplication(pid);

    CFStringRef name;
    AXUIElementCopyAttributeValue(ax_app, kAXTitleAttribute, (CFTypeRef *) &name);
    if (name == NULL) { return NULL; }
    name = CFStringCreateCopy(kCFAllocatorDefault, name);

    application *app = _create_application(ax_app, pid, name);

    return app;
}

bool applications_equal(application *a1, application *a2) {
    if (a1->pid == a2->pid
        && CFStringCompare(a1->name, a2->name, 0) == kCFCompareEqualTo) {
        return true;
    }
    return false;
}

// get application properties
AXUIElementRef get_application_AXUIElement(application *app) {
    return app->ax_app;
}

CFStringRef get_application_name(application *app) {
    return app->name;
}

pid_t get_application_pid(application *app) {
    return app->pid;
}

// deinit
void destroy_application(application *app) {
    CFRelease(app->name);
    CFRelease(app->ax_app);
    free(app);
}
