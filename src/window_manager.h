/// @file
/// @brief The file containing the relevant functions for managing windows.

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "./window.h"

/// @struct WindowListOptions
/// @brief A struct specifying the options to use when retrieving a list of
/// windows.
///
/// Some of the options provided may require an additional window to be
/// provided. Refer to Apple's documentation of the
/// [Window List Options
/// Constants](https://developer.apple.com/documentation/coregraphics/quartz_window_services/window_list_option_constants)
/// for more information.

/// @property WindowListOptions::all
/// @brief Retrieve all window elements.

/// @property WindowListOptions::on_screen_only
/// @brief Retrieve only on-screen window elements.

/// @property WindowListOptions::exclude_desktop_elements
/// @brief Exclude any window elements on the desktop.

/// @property WindowListOptions::including_window
/// @brief Include the window provided as an argument.

/// @property WindowListOptions::above_window
/// @brief Retrieve only window elements above the given window.

/// @property WindowListOptions::below_window
/// @brief Retrieve only window elements below the given window.
typedef struct {
    bool all;
    bool on_screen_only;
    bool exclude_desktop_elements;
    bool including_window;
    bool above_window;
    bool below_window;
} WindowListOptions;

/// @struct WindowList
/// @brief A struct containing a list of windows.
///
/// It contains an array to a pointer of windows, the number of windows
/// contained in the array, and the number of windows that can be containing
/// in the array. There should never be a need to manually adjust the contained
/// values. This functionality will be altered to be read-only in the future.

/// @property WindowList::count
/// @brief The number of windows in the array.

/// @property WindowList::capacity
/// @brief The maximum size of the array.

/// @property WindowList::windows
/// @brief An array containing a list of windows.
typedef struct {
    int      count;
    int      capacity;
    window **windows;
} WindowList;

/// @brief Retrieve a list of windows.
/// @param options A WindowListOptions struct containing the relevant options.
/// @param w The window which the results are relative to.
///
/// May be NULL depending on your options.
/// @returns Returns a WindowList struct containing the relevant information.
WindowList get_window_list(WindowListOptions options, window *window);

/// @brief Set the size and position of a given window.
/// @param window The window to move and/or resize.
/// @param new_frame The new size and position.
void set_window_frame(window *window, CGRect new_frame);

#endif
