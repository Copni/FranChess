//
// Created by IamaU on 31/08/2025.
//

#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void log_message(const LogLevel level, const char *format, ...) {
    const char *level_str[] = {"INFO", "WARNING", "ERROR"};
    const time_t now = time(NULL);
    struct tm *t = localtime(&now);

    FILE *f = fopen("log.txt", "a");
    if (!f) return; // sécurité si ouverture échoue

    fprintf(f, "[%02d-%02d-%04d %02d:%02d:%02d] [%s] ",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec,
            level_str[level]);

    va_list args;
    va_start(args, format);
    vfprintf(f, format, args); // version fichier de vprintf
    va_end(args);

    fprintf(f, "\n");
    fclose(f); // ferme le fichier
}


/* Exemple :
 *
int main() {
    log_message(INFO, "Programme démarré");
    log_message(WARNING, "Ceci est un avertissement");
    log_message(ERROR, "Erreur code %d", 404);
    return 0;
}
*/