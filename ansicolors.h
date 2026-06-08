#ifndef COLORS_H
#define COLORS_H
#include "sysinfo.h"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define RED     "\033[31m"

extern const char *ART[];



#define ART_LINES (int)(sizeof(ART) / sizeof(ART[0]))

#endif
