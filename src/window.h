/// @file
/// @brief The file containing functions related to window operations.

#ifndef WINDOW_H
#define WINDOW_H
#include "./application.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CGWindow.h>

/// @struct window
/// @brief An opaque type containing a window struct.
///
/// The application struct contains information regarding the window
/// which can be accessed with the relevant functions.
typedef struct _window window;

/// @brief Create and return a pointer to an opaque window struct.
/// @param window_dict The CFDictionaryRef containing the relevant window's information.
///
/// Acquired from CGWindowListCopyWindowInfo()
/// @return Returns a pointer to a window.
window *window_from_CFDictionary(CFDictionaryRef window_dict);

/// @brief Check if two windows are the same.
/// @param w1 The first window.
/// @param w2 The second window.
/// @return Returns true if they are the same, false if not.
bool windows_equal(window *w1, window *w2);

/// @brief Retrieve the AXUIElementRef associated with this window.
/// @param window The relevant window.
/// @return Returns the AXUIElementRef associated with this window.
AXUIElementRef get_window_AXUIElementRef(window *window);

/// @brief Retrieve the application associated with this window.
/// @param window The relevant window.
/// @return Returns the application associated with this window.
application *get_window_application(window *window);

/// @brief Retrieve the window ID associated with this window.
/// @param window The relevant window.
/// @return Returns the window ID associated with this window.
CGWindowID get_window_id(window *window);

/// @brief Retrieve the window's title.
/// @param window The relevant window.
/// @return Returns the CFStringRef containing the window's title.
CFStringRef get_window_title(window *window);

/// @brief Retrieve the window's frame.
/// @param window The relevant window.
/// @return Returns the window's frame (width, height, and x/y coordinates).
CGRect get_window_frame(window *window);

/// @brief Free the window struct and its contents.
/// @param app The window to remove from memory.
void destroy_window(window *window);

#endif
