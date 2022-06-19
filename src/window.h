/// @file
/// @brief The file containing functions related to window operations.

#ifndef WINDOW_H
#define WINDOW_H
#include "./application.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CGWindow.h>

/// @struct window
/// @brief A struct containing information regarding windows.
struct window {
    struct application *app;
    AXUIElementRef      ax_window;
    CGWindowID          id;
    CGRect              frame;
    CFStringRef         title;
};


/// @brief Create and return a pointer to an opaque window struct.
/// @param window_dict The CFDictionaryRef containing the relevant window's information.
/// @param err A pointer to an error variable to get the error code. May be null.
///
/// Acquired from CGWindowListCopyWindowInfo()
/// @return Returns a pointer to a window.
struct window *window_from_CFDictionary(CFDictionaryRef window_dict, enum error *err);

/// @brief Check if two windows are the same.
/// @param w1 The first window.
/// @param w2 The second window.
/// @return Returns true if they are the same, false if not. Returns false if either
/// pointer is null.
bool windows_equal(struct window *w1, struct window *w2);

/// @brief Free the window struct and its contents.
/// @param app The window to remove from memory.
void destroy_window(struct window *window);

#endif
