#include "sysinfo.h"
#include "ansicolors.h"
int main () {
    char hostname[64] = {0};
    char kernel[64] = {0};

    get_hostname(hostname, sizeof(hostname));
    get_kernel(kernel, sizeof(kernel));

    const char *user  = getenv("USER")  ?: "unknown";
    const char *shell = getenv("SHELL") ?: "unknown";
    const char *term  = getenv("TERM")  ?: "unknown";
    
    printf("\n");
    printf("  " BOLD CYAN "%s" RESET BOLD "@" CYAN "%s\n" RESET, user, hostname);
    printf("  " CYAN "────────────────────────────\n" RESET);
    
    printf("  " RED "Kernel  " RESET "  %s\n",       kernel);
    printf("  " RED "Shell   " RESET "  %s\n",       shell);
    printf("  " RED "Term    " RESET "  %s\n",       term);




}
