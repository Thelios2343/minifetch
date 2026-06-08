#ifndef SYSINFO_H
#define SYSINFO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF 256
#define ART_W 46

void get_hostname(char *out, size_t len);
void get_kernel(char *out, size_t len);
void get_cpu(char *model_out, size_t mlen, int *cores_out);
void get_memory(long *total_mib, long *used_mib);
void get_uptime(char *out, size_t len);
void get_loadavg(char *out, size_t len);
void get_distro(char *out, size_t len);
#endif
