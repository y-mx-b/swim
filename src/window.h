#ifndef WINDOW_H
#define WINDOW_H
#include "./application.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CGWindow.h>

typedef struct window window;

window *window_from_CFDictionary(CFDictionaryRef window_dict);

bool windows_equal(window *w1, window *w2);

AXUIElementRef get_window_AXUIElementRef(window *window);
application   *get_window_application(window *window);
CGWindowID     get_window_id(window *window);
CFStringRef    get_window_title(window *window);
CGRect         get_window_frame(window *window);

void destroy_window(window *window);

#endif
