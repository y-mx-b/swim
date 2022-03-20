#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "./window.h"

typedef struct {
    bool all;
    bool on_screen_only;
    bool exclude_desktop_elements;
    bool including_window;
    bool above_window;
    bool below_window;
} WindowListOptions;

typedef struct {
    int      count;
    int      capacity;
    window **windows;
} WindowList;

WindowList get_window_list(WindowListOptions options, window *window);

void move_window(window *window, CGRect new_frame);

#endif
