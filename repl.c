#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.c"

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer()
{
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void read_input(InputBuffer* input_buffer)
{
    ssize_t bytes_read =
	getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0) {
	printf("Error reading input\n");
	exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

void run_repl()
{
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
	printf("> ");
	read_input(input_buffer);
	if (strcmp(input_buffer->buffer, ".exit") == 0) {
	    close_input_buffer(input_buffer);
	    exit(EXIT_SUCCESS);
	}
	Lexer *lexer = new_lexer(input_buffer->buffer);
	Token *token = next_token(lexer);
	while (token->type != TokenTypeEOF) {
	    printf("literal=%s, type_idx=%d\n", token->literal, token->type);
	    token = next_token(lexer);
	}
    }
}
