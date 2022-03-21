/// @file
/// @brief The file containing the relevant functions for application operations.

#ifndef APPLICATION_H
#define APPLICATION_H
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

/// @struct application
/// @brief An opaque type containing an application struct.
///
/// The application struct contains information regarding the application
/// which can be accessed with the relevant functions.
typedef struct _application application;

/// @brief Create and return a pointer to an opaque application struct.
/// @param pid The PID to a macOS application.
/// @return Returns a pointer to an application.
application *create_application(pid_t pid);

/// @brief Check if two applications are the same.
/// @param a1 The first application.
/// @param a2 The second application.
/// @return Returns true if they are the same, false if not.
bool applications_equal(application *a1, application *a2);

/// @brief Retrive the AXUIElementRef associated with the application.
/// @param app The application.
/// @return The AXUIElementRef associated with the application.
AXUIElementRef get_application_AXUIElement(application *app);

/// @brief Retrieve the application's name.
/// @param app The application.
/// @return The CFStringRef containing the application's name.
CFStringRef get_application_name(application *app);

/// @brief Retrieve the application's PID.
/// @param app The application.
/// @return The application's PID.
pid_t get_application_pid(application *app);

/// @brief Free the application struct and its contents.
/// @param app The application to remove from memory.
void destroy_application();

#endif
