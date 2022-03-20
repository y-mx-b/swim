#include "../include/swim.h"
#include <CoreFoundation/CoreFoundation.h>

pid_t pid_from_CFNumber(CFNumberRef cf_pid) {
    pid_t pid;
    CFNumberGetValue(cf_pid, kCFNumberIntType, &pid);
    return pid;
}

CGWindowID window_id_from_CFNumber(CFNumberRef cf_window_id) {
    CGWindowID window_id;
    CFNumberGetValue(cf_window_id, kCGWindowIDCFNumberType, &window_id);
    return window_id;
}

char *cstring_from_CFString(CFStringRef cf_string) {
    CFIndex length = CFStringGetLength(cf_string);
    CFIndex size = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
    CFRange range = CFRangeMake(0, length);
    char *string = malloc(size);
    CFStringGetBytes(cf_string, range, kCFStringEncodingUTF8, '?', false, (unsigned char *) string, size, NULL);
    return string;
}
