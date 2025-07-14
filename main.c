#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s -f <filename> -t <task>\n", argv[0]);
        return 1;
    }

    char *filename = NULL;
    char *task = NULL;

    // Parsing command-line arguments
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
        } else if (strcmp(argv[i], "-t") == 0) {
            task = argv[i + 1];
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return 1;
        }
    }
    // Handling file opening error
    if (!filename || !task) {
        fprintf(stderr, "Missing filename or task\n");
        return 1;
    }

    FILE *addressFile = fopen(filename, "r");
    if (!addressFile) {
        perror("Failed to open address file");
        return 1;
    }

    if (strcmp(task, "task1") == 0) {
        task1(addressFile);
    } else if (strcmp(task, "task2") == 0) {
        task2(addressFile);
    } else if (strcmp(task, "task3") == 0) {
        task3(addressFile);
    } else if (strcmp(task, "task4") == 0) {
        task4(addressFile);
    }

    fclose(addressFile);
    return 0;
}
