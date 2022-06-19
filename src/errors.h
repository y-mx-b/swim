#ifndef ERRORS_H
#define ERRORS_H

#include <ApplicationServices/ApplicationServices.h>

/// @enum error
/// @brief An enum containing error codes.
enum error {
    NONE,
    NO_WINDOW,
    NO_APPLICATION,
    NULL_POINTER,
};

/// @brief Assign an error code to an error variable if the pointer is not null.
/// @param err A pointer to the error variable to assign the error code to.
/// @param e The error code to assign.
inline void assign_error(enum error *err, enum error e) {
    if (err != 0) { *err = e; }
}

/// @brief Get an error from an AXError type.
/// @param err An AXError error.
/// @return The matching error case for the AXError.
enum error error_from_AXError(AXError err);

#endif
