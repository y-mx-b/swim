#ifndef UTILITIES_H
#define UTILITIES_H
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

pid_t      pid_from_CFNumber(CFNumberRef cf_pid);
CGWindowID window_id_from_CFNumber(CFNumberRef cf_window_id);
char      *cstring_from_CFString(CFStringRef cf_string);

#endif
