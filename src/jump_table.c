#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jump_table.h"

int *build_jump_table(const char *code, int code_length) {
    int *jump_table = malloc(sizeof(int) * code_length);
    if (!jump_table) { fprintf(stderr, "Memory allocation error for jump_table.\n"); exit(EXIT_FAILURE); }
    int *stack = malloc(sizeof(int) * code_length);
    if (!stack) { fprintf(stderr, "Memory allocation error for stack.\n"); exit(EXIT_FAILURE); }
    int stack_ptr = 0;
    for (int i = 0; i < code_length; i++) {
        if (code[i] == '[')
            stack[stack_ptr++] = i;
        else if (code[i] == ']') {
            if (stack_ptr == 0) { fprintf(stderr, "Unmatched closing bracket at position %d.\n", i); exit(EXIT_FAILURE); }
            int start = stack[--stack_ptr];
            jump_table[start] = i;
            jump_table[i] = start;
        }
    }
    if (stack_ptr != 0) { fprintf(stderr, "Unmatched opening brackets.\n"); exit(EXIT_FAILURE); }
    free(stack);
    return jump_table;
}
