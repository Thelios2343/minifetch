#include "sysinfo.h"
#include "ansicolors.h"

void print_row(int art_idx, const char *info);


const char *ART[] = {
    "                    :==:              ",
    "               . ...-++-...          ",
    "             ..................       ",
    "         ::....:=++++++++++=:....::  ",
    "      :=====.-+++++=----==++++-.=====:",
    "    -=====.:++++-..........-++++:.=====-",
    "  -====: .:+++=.....:-::.....=+++:..:====-",
    ":====.  ..++++....=++++++=....++++... .====.",
    "====  ....+++-...-++++++++-...-+++....  ====",
    "====: ....+++=...:=++++++=:...=+++...  .====",
    " ====- ...=+++:....==++==....:+++=... -===-",
    "  -=====:..=+++-............-+++=. :=====",
    "  .::-=====.-++++=........=++++-.=====-.:.  ",
    " :+++. :-==...-=++++-  =++++=-...==-: :+++: ",
    "            .....=++=  =++=......        ",
    "              ...=++=  =++-...           ",
    "                 -++=  =++=              ",
    "        =++=:    =++=  =++=    .=++=     ",
    "         =++++==++++    =+++==++++=      ",
    "           :-====-:      .-====-:        ",
};



void print_row(int art_idx, const char *info) {
    
    if (art_idx >= 0 && art_idx < ART_LINES) {
        printf(BLUE "%-*s" RESET, ART_W, ART[art_idx]);
    } else {
        printf("%*s", ART_W, "");  
    }

    if (info) printf("  %s", info);
    printf("\n");
}


int main () {
    
    char hostname[64]   = {0};
    char kernel[64]     = {0};
    char cpu_model[96]  = {0};
    char uptime_s[64]   = {0};
    char loadavg_s[64]  = {0};
    char distro[128]    = {0};
    int  cpu_cores      = 0;
    long mem_total = 0, mem_used = 0;
 
    get_hostname(hostname, sizeof(hostname));
    get_kernel(kernel, sizeof(kernel));
    get_cpu(cpu_model, sizeof(cpu_model), &cpu_cores);
    get_memory(&mem_total, &mem_used);
    get_uptime(uptime_s, sizeof(uptime_s));
    get_loadavg(loadavg_s, sizeof(loadavg_s));
    get_distro(distro, sizeof(distro));
 
    const char *user  = getenv("USER")  ?: "unknown";
    const char *shell = getenv("SHELL") ?: "unknown";
    const char *term  = getenv("TERM")  ?: "unknown";
 
    /* — Barra de RAM — */
    int bar_w = 18;
    int filled = (mem_total > 0) ? (int)((float)mem_used / mem_total * bar_w) : 0;
    char bar[32] = {0};
    for (int i = 0; i < bar_w; i++) bar[i] = (i < filled) ? '#' : '.';
 
    
    char info[24][320];   
    memset(info, 0, sizeof(info));
    int r = 0;
 
    snprintf(info[r++], 320, BOLD CYAN "%s" RESET BOLD "@" CYAN "%s" RESET, user, hostname);
    snprintf(info[r++], 320, CYAN "────────────────────────────────" RESET);
    snprintf(info[r++], 320, BOLD GREEN "OS      " RESET "  %s", distro);
    snprintf(info[r++], 320, BOLD GREEN "Kernel  " RESET "  %s", kernel);
    snprintf(info[r++], 320, BOLD GREEN "Uptime  " RESET "  %s", uptime_s);
    snprintf(info[r++], 320, BOLD GREEN "Shell   " RESET "  %s", shell);
    snprintf(info[r++], 320, BOLD GREEN "Term    " RESET "  %s", term);
    snprintf(info[r++], 320, BOLD YELLOW "CPU     " RESET "  %s (%d cores)", cpu_model, cpu_cores);
    snprintf(info[r++], 320,
             BOLD MAGENTA "Memory  " RESET "  %ld / %ld MiB  [" GREEN "%s" RESET "]",
             mem_used, mem_total, bar);
    snprintf(info[r++], 320, BOLD BLUE "Load    " RESET "  %s", loadavg_s);
 
    
    char palette[320] = {0};
    const int codes[] = {40,41,42,43,44,45,46,47};
    for (int i = 0; i < 8; i++) {
        char tmp[16];
        snprintf(tmp, sizeof(tmp), "\033[%dm   ", codes[i]);
        strncat(palette, tmp, sizeof(palette) - strlen(palette) - 1);
    }
    strncat(palette, RESET, sizeof(palette) - strlen(palette) - 1);
    snprintf(info[r++], 320, "%s", palette);
 
    int total_info = r;   
 
    printf("\n");
 
    int total_rows = ART_LINES > total_info ? ART_LINES : total_info;

    int info_offset = (ART_LINES - total_info) / 2;
 
    for (int i = 0; i < total_rows; i++) {
        int art_i  = i;                     
        int info_i = i - info_offset;      
 
        const char *line_info = (info_i >= 0 && info_i < total_info)
                                 ? info[info_i]
                                 : NULL;
        print_row(art_i, line_info);
    }
 
    printf("\n");

    return 0;
 
} 
