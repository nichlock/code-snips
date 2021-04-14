# Colors

Linux console can show things with colors. Here's how to do that in C/C++, though the same strings will work anywhere.

```c++
const char COLOR_BLACK[]      = "\e[0;30m";
const char COLOR_D_GRAY[]     = "\e[1;30m";
const char COLOR_RED[]        = "\e[0;31m";
const char COLOR_L_RED[]      = "\e[1;31m";
const char COLOR_GREEN[]      = "\e[0;32m";
const char COLOR_L_GREEN[]    = "\e[1;32m";
const char COLOR_GOLD[]       = "\e[0;33m";
const char COLOR_YELLOW[]     = "\e[1;33m";
const char COLOR_BLUE[]       = "\e[0;34m";
const char COLOR_L_BLUE[]     = "\e[1;34m";
const char COLOR_PURPLE[]     = "\e[0;35m";
const char COLOR_L_PURPLE[]   = "\e[1;35m";
const char COLOR_CYAN[]       = "\e[0;36m";
const char COLOR_L_CYAN[]     = "\e[1;36m";
const char COLOR_L_GRAY[]     = "\e[0;37m";
const char COLOR_WHITE[]      = "\e[1;38m";

const char HIGHLIGHT_BLACK[]  = "\e[0;40m";
const char HIGHLIGHT_RED[]    = "\e[1;41m";
const char HIGHLIGHT_GREEN[]  = "\e[0;42m";
const char HIGHLIGHT_YELLOW[] = "\e[1;43m";
const char HIGHLIGHT_BLUE[]   = "\e[0;44m";
const char HIGHLIGHT_PURPLE[] = "\e[1;45m";
const char HIGHLIGHT_CYAN[]   = "\e[0;46m";
const char HIGHLIGHT_GRAY[]   = "\e[1;47m";

const char COLOR_NONE[]     = "\e[0m";
```

If these aren't working in some language, `\033` can go in place of `\e`. In windows shells or for files which should be colored, use the 'ESC' control character, which you can get by typing ALT+027 using a numberpad. You can also copy this: `` (after opening the `raw` file on GitHub).

This works directly in console echos too, with:

```shell
RED='\e[0;31m'
NC='\e[0m'
echo -e "This text is ${RED}red${NC}."
```

