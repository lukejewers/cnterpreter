#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"



void read_char(Lexer *lexer)
{
    if (lexer->read_position >= lexer->input_length) {
	lexer->ch = '\0';
    } else {
	lexer->ch = lexer->input[lexer->read_position];
    }
    lexer->position = lexer->read_position;
    lexer->read_position++;
}

char peek_char(Lexer *lexer)
{
    if (lexer->read_position >= lexer->input_length) {
	return '\0';
    } else {
	return lexer->input[lexer->read_position];
    }
}


Token *new_token(TokenType token_type, char *ch)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = token_type;
    token->literal = ch;
    return token;
}

bool is_letter(char ch)
{
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

int is_number(char ch)
{
    return '0' <= ch && '9' >= ch;
}

void skip_whitespace(Lexer *lexer)
{
    while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r') {
	read_char(lexer);
    }
}

char *read_identifier(Lexer *lexer)
{
    int position = lexer->position;
    while (is_letter(lexer->ch)) {
	read_char(lexer);
    }
    char *str = malloc(10 * sizeof(char*));
    int len = lexer->position - position;
    char* src = lexer->input + position;
    strncpy(str, src, len);
    return str;
}

char *read_number(Lexer *lexer)
{
    int position = lexer->position;
    while (is_number(lexer->ch)) {
	read_char(lexer);
    }
    char *str = malloc(10 * sizeof(char*));
    int len = lexer->position - position;
    char* src = lexer->input + position;
    strncpy(str, src, len);
    return str;
}

TokenType lookup_ident(char* literal)
{
    if (strcmp(literal, "fn") == 0) {
	return TokenTypeFunction;
    } else if (strcmp(literal, "let") == 0) {
	return TokenTypeLet;
    } else if (strcmp(literal, "true") == 0) {
	return TokenTypeTrue;
    } else if (strcmp(literal, "false") == 0) {
	return TokenTypeFalse;
    } else if (strcmp(literal, "if") == 0) {
	return TokenTypeIf;
    } else if (strcmp(literal, "else") == 0) {
	return TokenTypeElse;
    } else if (strcmp(literal, "return") == 0) {
	return TokenTypeReturn;
    }
    return TokenTypeIdent;
}

Token *next_token(Lexer *lexer)
{
    Token *token;
    skip_whitespace(lexer);
    switch (lexer->ch) {
    case '=':
	if (peek_char(lexer) == '=') {
	    read_char(lexer);
	    token = new_token(TokenTypeEq, "==");
	} else {
	    token = new_token(TokenTypeAssign, &lexer->ch);
	}
	break;
    case ';':
	token = new_token(TokenTypeSemicolon, &lexer->ch);
	break;
    case '(':
	token = new_token(TokenTypeLParen, &lexer->ch);
	break;
    case ')':
	token = new_token(TokenTypeRParen, &lexer->ch);
	break;
    case ',':
	token = new_token(TokenTypeComma, &lexer->ch);
	break;
    case '+':
	token = new_token(TokenTypePlus, &lexer->ch);
	break;
    case '-':
	token = new_token(TokenTypeMinus, &lexer->ch);
	break;
    case '!':
	if (peek_char(lexer) == '=') {
	    read_char(lexer);
	    token = new_token(TokenTypeNotEq, "!=");
	} else {
	    token = new_token(TokenTypeBang, &lexer->ch);
	}
	break;
    case '/':
	token = new_token(TokenTypeSlash, &lexer->ch);
	break;
    case '*':
	token = new_token(TokenTypeAsterisk, &lexer->ch);
	break;
    case '<':
	token = new_token(TokenTypeLT, &lexer->ch);
	break;
    case '>':
	token = new_token(TokenTypeGT, &lexer->ch);
	break;
    case '{':
	token = new_token(TokenTypeLBrace, &lexer->ch);
	break;
    case '}':
	token = new_token(TokenTypeRBrace, &lexer->ch);
	break;
    case '\0':
	token = new_token(TokenTypeEOF, &lexer->ch);
	break;
    default:
	if (is_letter(lexer->ch)) {
	    char *token_literal = read_identifier(lexer);
	    TokenType token_type = lookup_ident(token_literal);
	    token = new_token(token_type, token_literal);
	    return token;
	} else if (is_number(lexer->ch)) {
	    char *token_literal = read_number(lexer);
	    token = new_token(TokenTypeInt, token_literal);
	    return token;
	} else {
	    token = new_token(TokenTypeIllegal, &lexer->ch);
	}
    }
    read_char(lexer);
    return token;
}

Lexer *new_lexer(char *string)
{
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    lexer->input_length = strlen(string);
    lexer->input = string;
    lexer->position = 0;
    lexer->read_position = 0;
    read_char(lexer);
    return lexer;
}
