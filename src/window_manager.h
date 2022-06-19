/// @file
/// @brief The file containing the relevant functions for managing windows.

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "./window.h"

/// @struct window_list_options
/// @brief A struct specifying the options to use when retrieving a list of
/// windows.
///
/// Some of the options provided may require an additional window to be
/// provided. Refer to Apple's documentation of the
/// [Window List Options
/// Constants](https://developer.apple.com/documentation/coregraphics/quartz_window_services/window_list_option_constants)
/// for more information.

/// @property window_list_options::all
/// @brief Retrieve all window elements.

/// @property window_list_options::on_screen_only
/// @brief Retrieve only on-screen window elements.

/// @property window_list_options::exclude_desktop_elements
/// @brief Exclude any window elements on the desktop.

/// @property window_list_options::including_window
/// @brief Include the window provided as an argument.

/// @property window_list_options::above_window
/// @brief Retrieve only window elements above the given window.

/// @property window_list_options::below_window
/// @brief Retrieve only window elements below the given window.
typedef struct {
    bool all;
    bool on_screen_only;
    bool exclude_desktop_elements;
    bool including_window;
    bool above_window;
    bool below_window;
} window_list_options;

/// @struct window_list
/// @brief A struct containing a list of windows.
///
/// It contains an array to a pointer of windows, the number of windows
/// contained in the array, and the number of windows that can be containing
/// in the array. There should never be a need to manually adjust the contained
/// values. This functionality will be altered to be read-only in the future.

/// @property window_list::count
/// @brief The number of windows in the array.

/// @property window_list::capacity
/// @brief The maximum size of the array.

/// @property window_list::windows
/// @brief An array of pointers ot windows..
typedef struct {
    int             count;
    int             capacity;
    struct window **windows;
} window_list;

/// @brief Retrieve a list of windows.
/// @param options A window_list_options struct containing the relevant options.
/// @param w The window which the results are relative to.
/// @param err A pointer to an error variable to get the error code. May be null.
///
/// May be NULL depending on your options.
/// @returns Returns a window_list struct containing the relevant information.
window_list
        get_window_list(window_list_options options, struct window *w, enum error *err);

/// @brief Set the size and position of a given window.
/// @param window The window to move and/or resize.
/// @param new_frame The new size and position.
/// @param err A pointer to an error variable to get the error code. May be null.
///
/// Size and position are assigned separately, so in the case that there are two errors,
/// the last error will be returned.
void set_window_frame(struct window *window, CGRect new_frame, enum error *err);

#endif
