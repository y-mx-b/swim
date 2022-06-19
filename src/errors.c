#include "../include/swim.h"
#include <ApplicationServices/ApplicationServices.h>

enum error error_from_AXError(AXError err) {
    switch (err) {
    case kAXErrorSuccess:
        return NONE;
    case kAXErrorAPIDisabled:
        return NO_PERMISSIONS;
    case kAXErrorActionUnsupported:
        return NO_ATTRIBUTE;
    case kAXErrorInvalidUIElement:
        return NO_ELEMENT;
    default:
        return UNKNOWN;
    }
}
