#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void
runautostart(void)
{
    char *pathpfx;
    char *path;
    char *xdgdatahome;
    char *home;
    struct stat sb;
    FILE *log_file = fopen("/home/renzo/renzo.log", "a");

    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    if ((home = getenv("HOME")) == NULL) {
        fprintf(log_file, "DEBUG: HOME environment variable is not set. (if: false)\n");
        fclose(log_file);
        return;
    }

    fprintf(log_file, "DEBUG: HOME is set to: %s (if: true)\n", home);

    /* if $XDG_DATA_HOME is set and not empty, use $XDG_DATA_HOME/dwm,
     * otherwise use ~/.local/share/dwm as autostart script directory
     */
    xdgdatahome = getenv("XDG_DATA_HOME");
    if (xdgdatahome != NULL && *xdgdatahome != '\0') {
        fprintf(log_file, "DEBUG: XDG_DATA_HOME is set to: %s (if: true)\n", xdgdatahome);
        /* space for path segments, separators and nul */
        pathpfx = ecalloc(1, strlen(xdgdatahome) + strlen(dwmdir) + 2);

        if (sprintf(pathpfx, "%s/%s", xdgdatahome, dwmdir) <= 0) {
            fprintf(log_file, "DEBUG: Failed to create path using XDG_DATA_HOME. (if: true)\n");
            free(pathpfx);
            fclose(log_file);
            return;
        }

        fprintf(log_file, "DEBUG: Path prefix is: %s (if: true)\n", pathpfx);
    } else {
        fprintf(log_file, "DEBUG: XDG_DATA_HOME is not set or empty. (if: false)\n");
        /* space for path segments, separators and nul */
        pathpfx = ecalloc(1, strlen(home) + strlen(localshare) + strlen(dwmdir) + 3);

        if (sprintf(pathpfx, "%s/%s/%s", home, localshare, dwmdir) < 0) {
            fprintf(log_file, "DEBUG: Failed to create path using HOME and localshare. (if: true)\n");
            free(pathpfx);
            fclose(log_file);
            return;
        }

        fprintf(log_file, "DEBUG: Path prefix is: %s (if: true)\n", pathpfx);
    }

/* check if the autostart script directory exists */
    if (stat(pathpfx, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        fprintf(log_file, "DEBUG: Path %s exists and is a directory. (if: true)\n", pathpfx);
    } else {
        fprintf(log_file, "DEBUG: Path %s does not exist or is not a directory. (if: false)\n", pathpfx);
        /* the XDG conformant path does not exist or is no directory
         * so we try ~/.dwm instead
         */
        char *pathpfx_new = realloc(pathpfx, strlen(home) + strlen(dwmdir) + 3);
        if (pathpfx_new == NULL) {
            fprintf(log_file, "DEBUG: Failed to reallocate path prefix. (if: true)\n");
            free(pathpfx);
            fclose(log_file);
            return;
        }
        pathpfx = pathpfx_new;

        if (sprintf(pathpfx, "%s/.%s", home, dwmdir) <= 0) {
            fprintf(log_file, "DEBUG: Failed to create path using HOME and dwmdir. (if: true)\n");
            free(pathpfx);
            fclose(log_file);
            return;
        }

        fprintf(log_file, "DEBUG: New path prefix is: %s (if: true)\n", pathpfx);
    }

    /* try the blocking script first */
    path = ecalloc(1, strlen(pathpfx) + strlen(autostartblocksh) + 2);
    if (sprintf(path, "%s/%s", pathpfx, autostartblocksh) <= 0) {
        fprintf(log_file, "DEBUG: Failed to create path for blocking script. (if: true)\n");
        free(path);
        free(pathpfx);
        fclose(log_file);
        return;
    }

    fprintf(log_file, "DEBUG: Blocking script path is: %s (if: true)\n", path);

    if (access(path, X_OK) == 0) {
        fprintf(log_file, "DEBUG: Running blocking script: %s (if: true)\n", path);
        system(path);
    } else {
        fprintf(log_file, "DEBUG: Blocking script %s does not exist or is not executable. (if: false)\n", path);
    }

/* now the non-blocking script */
    if (sprintf(path, "%s/%s", pathpfx, autostartsh) <= 0) {
        fprintf(log_file, "DEBUG: Failed to create path for non-blocking script. (if: true)\n");
        free(path);
        free(pathpfx);
        fclose(log_file);
        return;
    }

    fprintf(log_file, "DEBUG: Non-blocking script path is: %s (if: true)\n", path);

    if (access(path, X_OK) == 0) {
        fprintf(log_file, "DEBUG: Running non-blocking script: %s (if: true)\n", path);
        system(strcat(path, " &"));
    } else {
        fprintf(log_file, "DEBUG: Non-blocking script %s does not exist or is not executable. (if: false)\n", path);
    }

    free(pathpfx);
    free(path);
    fclose(log_file);
}