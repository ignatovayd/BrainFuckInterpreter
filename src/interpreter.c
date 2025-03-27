#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#define TAPE_SIZE 30000

static void print_debug(const char *tape, int tape_ptr) {
    int start = tape_ptr - 5;
    if (start < 0) start = 0;
    int end = tape_ptr + 5;
    if (end > TAPE_SIZE) end = TAPE_SIZE;
    printf("\n[DEBUG] Tape[%d]: ", tape_ptr);
    for (int i = start; i < end; i++) {
        if (i == tape_ptr)
            printf("(%d) ", tape[i]);
        else
            printf("%d ", tape[i]);
    }
    printf("\n");
}

void interpret(const char *code, int *jump_table, int debug) {
    char tape[TAPE_SIZE] = {0};
    int tape_ptr = 0, pc = 0, code_length = strlen(code);
    while (pc < code_length) {
        char command = code[pc];
        switch (command) {
            case '>': tape_ptr++; if (tape_ptr >= TAPE_SIZE) { fprintf(stderr, "Tape pointer overflow at position %d.\n", pc); exit(EXIT_FAILURE); } break;
            case '<': tape_ptr--; if (tape_ptr < 0) { fprintf(stderr, "Tape pointer underflow at position %d.\n", pc); exit(EXIT_FAILURE); } break;
            case '+': tape[tape_ptr]++; break;
            case '-': tape[tape_ptr]--; break;
            case '.': putchar(tape[tape_ptr]); break;
            case ',': tape[tape_ptr] = getchar(); break;
            case '[': if (tape[tape_ptr] == 0) pc = jump_table[pc]; break;
            case ']': if (tape[tape_ptr] != 0) pc = jump_table[pc]; break;
            default: break;
        }
        if (debug) print_debug(tape, tape_ptr);
        pc++;
    }
}
