/// @file
/// @brief The file containing various utility functions.

#ifndef UTILITIES_H
#define UTILITIES_H
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

/// @brief Retrieve a PID from a CFNumberRef.
///
/// This function is intended solely for internal use. There should be no
/// need to call this externally. It will eventually be moved to an
/// internally-used header file.
/// @param cf_pid The CFNumberRef containing the PID.
/// @return Returns the PID.
pid_t pid_from_CFNumber(CFNumberRef cf_pid);

/// @brief Retrieve a window ID from a CFNumberRef.
///
/// This function is intended solely for internal use. There should be no
/// need to call this externally. It will eventually be moved to an
/// internally-used header file.
/// @param cf_window_id The CFNumberRef containing the window ID.
/// @return Returns the window ID.
CGWindowID window_id_from_CFNumber(CFNumberRef cf_window_id);

/// @brief Retrieve C-string from a CFStringRef.
/// @param cf_string The CFStringRef.
/// @return Returns a pointer to a C-string (null-terminated).
char *cstring_from_CFString(CFStringRef cf_string);

#endif
