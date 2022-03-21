/// @file
/// @brief The file containing functions related to checking/requesting permissions.

#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <stdbool.h>

/// @brief Check for and/or request accessibility permissions.
///
/// Required in order to move windows and access certain information regarding
/// windows.
/// @return true if accessibility permissions have been granted, false if not.
bool request_accessibility_permissions();

/// @brief Check for and/or request screen recording permissions.
///
/// Required in order to access window titles (macOS 10.15+) and for showing
/// PIP windows (planned feature).
/// @return true is accessibility permissions have been granted, false if not.
bool request_screen_recording_permissions();

#endif
