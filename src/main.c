#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "jump_table.h"

int main(int argc, char *argv[]) {
    int debug = 0;
    char *filename = NULL;
    if (argc < 2) { fprintf(stderr, "Usage: %s [-d] <filename>\n", argv[0]); exit(EXIT_FAILURE); }
    if (argc == 2) filename = argv[1];
    else if (argc == 3) {
        if (strcmp(argv[1], "-d") == 0) { debug = 1; filename = argv[2]; }
        else if (strcmp(argv[2], "-d") == 0) { debug = 1; filename = argv[1]; }
        else { fprintf(stderr, "Usage: %s [-d] <filename>\n", argv[0]); exit(EXIT_FAILURE); }
    }
    FILE *file = fopen(filename, "r");
    if (!file) { perror("File open error"); exit(EXIT_FAILURE); }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *code = malloc(file_size + 1);
    if (!code) { fprintf(stderr, "Memory allocation error for code.\n"); fclose(file); exit(EXIT_FAILURE); }
    size_t read_size = fread(code, 1, file_size, file);
    code[read_size] = '\0';
    fclose(file);
    int *jump_table = build_jump_table(code, strlen(code));
    interpret(code, jump_table, debug);
    free(code);
    free(jump_table);
    return EXIT_SUCCESS;
}
