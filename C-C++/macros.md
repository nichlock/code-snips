Printer macros:
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
Macro call & (uncolored) text printed: 
```c++ 
warn_printf("Stop called after program ended, sim time not available.");
```
> Internal Warning: Stop called after program ended, sim time not available. [from timer_stop (in vpi_files/VpiMain.cpp:108)]
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
