#ifndef DEBUG_H
#define DEBUG_H

///
/// THIS FILE IS NOT IMPLEMENTED BY CORE!
///
/// Debugging is going to be platform specific.
/// For nds, we use the arm interrupt specific
/// for debugging.
///
/// For unix_opengl, its different.
///
/// NOTE: All debug print helpers will print a
/// newline.
///

/// 
/// Somehow displays a message, and nothing else.
///
void debug_info(const char *msg_fmt, ...);

/// 
/// Somehow displays a warning, and nothing else.
///
void debug_warning(const char *msg_fmt, ...);

/// 
/// Somehow displays an error, and if possible for
/// the given backend, creates a core dump.
///
void debug_error(const char *msg_fmt, ...);

///
/// Somehow displays an error (maybe only briefly!)
/// and halts code execution.
///
void debug_abort(const char *msg_fmt, ...);

#endif
