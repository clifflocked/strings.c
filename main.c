#include <stdio.h>
#include <ctype.h>
#include <string.h>

void strings(FILE *f) {
    char buf[1024];
    int c, bufidx = 0;
    while ((c = fgetc(f)) != EOF) {
        if (isprint(c)) {
            buf[bufidx++] = c;
            if (bufidx > 1022) {
                buf[1023] = '\0';
                printf(buf);
                bufidx = 0;
            }
        } else {
            if (bufidx > 3) {
                buf[bufidx] = '\0';
                printf(buf);
                putchar('\n');
                bufidx = 0;
            } else {
                bufidx = 0;
            }
        }
    }
    if (bufidx > 3) {
        buf[bufidx] = '\0';
        printf(buf);
        putchar('\n');
    }
}

void print_help() {
    puts("Usage: strings [FILE]...");
    puts("Print strings in FILE(s), or from stdin if none specified");
}

int main(int argc, char **argv) {
    if (argc == 1)
        strings(stdin);
    else if (argc == 2 && strcmp(argv[1], "-h") == 0)
        print_help();
    else for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        strings(f);
        fclose(f);
    }
}
