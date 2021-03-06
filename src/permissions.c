#include "../include/swim.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreVideo/CVPixelBuffer.h>
#include <stdbool.h>

bool request_accessibility_permissions() {
    bool                       result          = false;
    CFDictionaryKeyCallBacks   key_callbacks   = kCFTypeDictionaryKeyCallBacks;
    CFDictionaryValueCallBacks value_callbacks = kCFTypeDictionaryValueCallBacks;

    CFStringRef  key   = kAXTrustedCheckOptionPrompt;
    CFBooleanRef value = kCFBooleanTrue;

    CFDictionaryRef options = CFDictionaryCreate(
            kCFAllocatorDefault, (CFTypeRef *) &key, (CFTypeRef *) &value, 1,
            &key_callbacks, &value_callbacks);
    result = AXIsProcessTrustedWithOptions(options);

    CFRelease(key);
    CFRelease(value);
    CFRelease(options);

    return result;
}

bool request_screen_recording_permissions() {
    CGDisplayStreamRef stream = NULL;
    stream                    = CGDisplayStreamCreate(
                               CGMainDisplayID(), 1, 1, kCVPixelFormatType_32BGRA, nil,
                               ^(CGDisplayStreamFrameStatus status, uint64_t displayTime,
              IOSurfaceRef frameSurface, CGDisplayStreamUpdateRef updateRef){});
    if (stream == NULL) { return false; }
    CFRelease(stream);
    return true;
}
