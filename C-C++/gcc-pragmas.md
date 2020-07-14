Hide a warning in a block of code

```c++
// Save current diagnostics settings
#pragma GCC diagnostic push
// Warns on "-Wformat"
#pragma GCC diagnostic warning "-Wformat"
// Causes an error on "-Wformat"
#pragma GCC diagnostic error "-Wformat"
 // Does nothing on "-Wformat"
#pragma GCC diagnostic ignored "-Wformat"

/* Code goes here */

// Return to saved settings.
#pragma GCC diagnostic pop
```

Show something during compilation:

```c++
#pragma GCC message "This message, in " __FILE__  ", shows up in the GCC output as a message"
#pragma GCC warning "This message, in " __FILE__ ", shows up in the GCC output as a warning"
#pragma GCC error "This message, in " __FILE__ ", shows up in the GCC output as an error"
```

This code from the GCC docs will print the following:

```c++
// Neat trick from GNU GCC docs:
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

TODO(Remember to fix this)
```

> /tmp/file.c:4: note: #pragma message: TODO - Remember to fix this
