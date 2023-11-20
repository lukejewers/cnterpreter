#include <stddef.h>

typedef enum {
    TokenTypeEOF,
    TokenTypeIllegal,
    TokenTypeIdent,
    TokenTypeInt,
    TokenTypeAssign,
    TokenTypeEq,
    TokenTypeNotEq,
    TokenTypeTrue,
    TokenTypeFalse,
    TokenTypeIf,
    TokenTypeElse,
    TokenTypeReturn,
    TokenTypePlus,
    TokenTypeMinus,
    TokenTypeLT,
    TokenTypeGT,
    TokenTypeBang,
    TokenTypeAsterisk,
    TokenTypeSlash,
    TokenTypeComma,
    TokenTypeSemicolon,
    TokenTypeLParen,
    TokenTypeRParen,
    TokenTypeLBrace,
    TokenTypeRBrace,
    TokenTypeFunction,
    TokenTypeLet,
} TokenType;

typedef struct Token {
    TokenType type;
    char *literal;
} Token;

typedef struct Lexer {
    char *input;
    size_t input_length;
    size_t position;
    size_t read_position;
    char ch;
} Lexer;


Token *next_token(Lexer *lexer);
Token *new_token(TokenType token_type, char *ch);
Lexer *new_lexer(char *string);
