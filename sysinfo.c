#include "sysinfo.h"

#define BUF 256

void get_hostname(char *out, size_t len) {
    FILE *f = fopen("/proc/sys/kernel/hostname", "r");

    if (f) {
        if (fgets(out, len, f)) {
            /* fgets incluye '\n', lo eliminamos */
            out[strcspn(out, "\n")] = '\0';
        }
        fclose(f);
    }
}

void get_kernel(char *out, size_t len) {
    FILE *f = fopen("/proc/version", "r");
    
    if (!f) { snprintf(out, len, "unknown"); return; }
    
    char line [512];

    if (fgets(line, sizeof(line), f)) {
        
        char *ver = strstr(line, "version ");
    
    if (ver) { 
        ver += 8;

        size_t i = 0;
        
        while (ver[i] && ver [i] != ' ' && i < len -1) {
            out[i] = ver [i];
            ++i;
        }
        out[i] = '\0';
    }
}
fclose(f);
}
