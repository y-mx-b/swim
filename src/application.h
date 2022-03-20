#ifndef APPLICATION_H
#define APPLICATION_H
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

typedef struct application application;

application *create_application(pid_t pid);

bool applications_equal(application *a1, application *a2);

AXUIElementRef get_application_AXUIElement(application *app);
CFStringRef    get_application_name(application *app);
pid_t          get_application_pid(application *app);

void destroy_application();

#endif
