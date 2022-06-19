/// @file
/// @brief The file containing the relevant functions for application operations.

#ifndef APPLICATION_H
#define APPLICATION_H
#include "errors.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

/// @struct application
/// @brief A struct containing information regarding applications.
struct application {
    AXUIElementRef ax_app;
    pid_t          pid;
    CFStringRef    name;
};


/// @brief Create and return a pointer to an opaque application struct.
/// @param pid The PID to a macOS application.
/// @param err A pointer to an error variable to get the error code. May be null.
/// @return Returns a pointer to an application.
struct application *create_application(pid_t pid, enum error *err);

/// @brief Check if two applications are the same.
/// @param a1 The first application.
/// @param a2 The second application.
/// @return Returns true if they are the same, false if not. Will also return false if
/// either pointer is null.
bool applications_equal(struct application *a1, struct application *a2);

/// @brief Free the application struct and its contents.
/// @param app The application to remove from memory.
void destroy_application(struct application *app);

#endif
