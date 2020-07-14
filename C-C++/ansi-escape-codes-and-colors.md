# Colors

Credit to [Tobias](https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux) for the formatting, numbers, and shell code!

Linux console can show things with colors. Here's how to do that in C/C++, though the same strings will work anywhere.

```c++
const char COLOR_BLACK[]    = "\e[0;30m";
const char COLOR_D_GRAY[]   = "\e[1;30m";
const char COLOR_RED[]      = "\e[0;31m";
const char COLOR_L_RED[]    = "\e[1;31m";
const char COLOR_GREEN[]    = "\e[0;32m";
const char COLOR_L_GREEN[]  = "\e[1;32m";
const char COLOR_ORANGE[]   = "\e[0;33m";
const char COLOR_YELLOW[]   = "\e[1;33m";
const char COLOR_BLUE[]     = "\e[0;34m";
const char COLOR_L_BLUE[]   = "\e[1;34m";
const char COLOR_PURPLE[]   = "\e[0;35m";
const char COLOR_L_PURPLE[] = "\e[1;35m";
const char COLOR_CYAN[]     = "\e[0;36m";
const char COLOR_L_CYAN[]   = "\e[1;36m";
const char COLOR_L_GRAY[]   = "\e[0;37m";
const char COLOR_WHITE[]    = "\e[1;38m";
const char COLOR_NONE[]     = "\e[0m";
```

If these aren't working in some language, `\033` can go in place of `\e`.

This works directly in console echos too, with:

```shell
RED='\e[0;31m'
NC='\e[0m'
echo -e "I ${RED}love${NC} Stack Overflow"
```
