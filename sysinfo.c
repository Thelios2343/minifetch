#include "sysinfo.h"
#include "ansicolors.h"
void get_hostname(char *out, size_t len) {
    FILE *f = fopen("/proc/sys/kernel/hostname", "r");

    if (f) {
        if (fgets(out, len, f)) {
            
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

void get_cpu(char *model_out, size_t mlen, int *cores_out) {
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) { snprintf(model_out, mlen, "desconocido"); *cores_out = 0; return; }
    char line[BUF];
    int found = 0;
    *cores_out = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "processor", 9) == 0) (*cores_out)++;
        if (!found && strncmp(line, "model name", 10) == 0) {
            char *c = strchr(line, ':');
            if (c) {
                c += 2;
                strncpy(model_out, c, mlen - 1);
                model_out[mlen - 1] = '\0';
                model_out[strcspn(model_out, "\n")] = '\0';
                found = 1;
            }
        }
    }
    fclose(f);
    if (!found) snprintf(model_out, mlen, "unknown");
}

void get_memory(long *total_mib, long *used_mib) {
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) { *total_mib = *used_mib = 0; return; }
    char line[BUF];
    long total_kb = 0, avail_kb = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "MemTotal:", 9) == 0)
            sscanf(line, "MemTotal: %ld kB", &total_kb);
        else if (strncmp(line, "MemAvailable:", 13) == 0)
            sscanf(line, "MemAvailable: %ld kB", &avail_kb);
    }
    fclose(f);
    *total_mib = total_kb / 1024;
    *used_mib  = (total_kb - avail_kb) / 1024;
}

void get_uptime(char *out, size_t len) {
    FILE *f = fopen("/proc/uptime", "r");
    if (!f) { snprintf(out, len, "desconocido"); return; }
    double up;
    fscanf(f, "%lf", &up);
    fclose(f);
    long s = (long)up;
    int d = s / 86400, h = (s % 86400) / 3600, m = (s % 3600) / 60;
    if (d > 0) snprintf(out, len, "%dd %dh %dm", d, h, m);
    else if (h > 0) snprintf(out, len, "%dh %dm", h, m);
    else snprintf(out, len, "%dm", m);
}

void get_loadavg(char *out, size_t len) {
    FILE *f = fopen("/proc/loadavg", "r");
    if (!f) { snprintf(out, len, "desconocido"); return; }
    float l1, l5, l15;
    fscanf(f, "%f %f %f", &l1, &l5, &l15);
    fclose(f);
    snprintf(out, len, "%.2f  %.2f  %.2f", l1, l5, l15);
}


void get_distro(char *out, size_t len) {
    FILE *f = fopen("/etc/os-release", "r");
    if (!f) { snprintf(out, len, "Linux"); return; }
    char line[BUF];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
            char *val = line + 12;
            if (*val == '"') val++;
            val[strcspn(val, "\"\n")] = '\0';
            strncpy(out, val, len - 1);
            out[len - 1] = '\0';
            fclose(f);
            return;
        }
    }
    fclose(f);
    snprintf(out, len, "Linux");
}

