Colorful printing macros, for C++ 2a:
```c++
// Colorful printout of warnings and errors that also show where they came from
#define warn_printf(a, ...) \
	printf("\e[1;33mInternal Warning: " a "\e[0;37m [from %s (in %s:%d)]\e[0m\n" \
	       __VA_OPT__(, ) __VA_ARGS__,  \
	       __FUNCTION__, __FILE__, __LINE__)
#define error_printf(a, ...) \
	printf("\e[1;31mInternal Error: " a "\e[0;37m [from %s (in %s:%d)]\e[0m\n" \
	       __VA_OPT__(, ) __VA_ARGS__,  \
	       __FUNCTION__, __FILE__, __LINE__)
```

> Internal Warning: Stop called after program ended, sim time not available. [from timer_stop (in vpi_files/VpiMain.cpp:108)]

For earlier C++, use `, ##__VA_ARGS__` in place of `__VA_OPT__(, ) __VA_ARGS__`.

---
Stringizing and conacatentation (from GNU/GCC docs):
```c++
// Replace this:
struct command commands[] =
{
  { "quit", quit_command },
  { "help", help_command },
};

// With this:
#define COMMAND(NAME)  { #NAME, NAME ## _command }

struct command commands[] =
{
  COMMAND (quit),
  COMMAND (help),
};
```
