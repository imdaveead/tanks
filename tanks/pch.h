#pragma once

// Disable conversion warnings
#pragma warning(disable:4244)
// Disable compiler option warnings that idk how to fix
#pragma warning(disable:4652)

// Formatted Date
#define BUILD_DATESTAMP (std::string() + __DATE__[7] + __DATE__[8] + __DATE__[9] + __DATE__[10] + "-" + (\
  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? "01" : "06") \
: __DATE__ [2] == 'b' ? "02" \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? "03" : "04") \
: __DATE__ [2] == 'y' ? "05" \
: __DATE__ [2] == 'l' ? "07" \
: __DATE__ [2] == 'g' ? "08" \
: __DATE__ [2] == 'p' ? "09" \
: __DATE__ [2] == 't' ? "10" \
: __DATE__ [2] == 'v' ? "11" \
: "12") + "-" + (__DATE__[4] == ' ' ? '0' : __DATE__[4]) + __DATE__[5])

#define PRINTF_ENABLE false
#if PRINTF_ENABLE
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...) /*Do Nothing*/
#endif
