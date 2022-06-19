#ifndef ERRORS_H
#define ERRORS_H

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

#endif
