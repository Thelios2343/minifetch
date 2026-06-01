#ifndef SYSINFO_H
#define SYSINFO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF 256

void get_hostname(char *out, size_t len);
void get_kernel(char *out, size_t len);


#endif
