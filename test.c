#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char *input_0 = "=+(){},;";
char *input_1 =
    "let five = 5;" \
    "let ten = 10;" \
    "let add = fn(x, y) {" \
    "  x + y;" \
    "};" \
    "let result = add(five, ten);";
char *input_2 =
    "!-/*5;" \
    "5 < 10 > 5;";
char *input_3 =
    "if (5 < 10) {" \
    "  return true;" \
    "} else {" \
    "  return false;" \
    "}";
char *input_4 =
    "10 == 10;" \
    "10 != 9;";

#define expected_tokens_0_len 9
Token expected_tokens_0[expected_tokens_0_len] = {
    {TokenTypeAssign,	 "="},
    {TokenTypePlus,	 "+"},
    {TokenTypeLParen,	 "("},
    {TokenTypeRParen,	 ")"},
    {TokenTypeLBrace,	 "{"},
    {TokenTypeRBrace,	 "}"},
    {TokenTypeComma,	 ","},
    {TokenTypeSemicolon, ";"},
    {TokenTypeEOF,	 ""}
};
#define expected_tokens_1_len 37
Token expected_tokens_1[expected_tokens_1_len] = {
    {TokenTypeLet, "let"},
    {TokenTypeIdent, "five"},
    {TokenTypeAssign, "="},
    {TokenTypeInt, "5"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeLet, "let"},
    {TokenTypeIdent, "ten"},
    {TokenTypeAssign, "="},
    {TokenTypeInt, "10"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeLet, "let"},
    {TokenTypeIdent, "add"},
    {TokenTypeAssign, "="},
    {TokenTypeFunction, "fn"},
    {TokenTypeLParen, "("},
    {TokenTypeIdent, "x"},
    {TokenTypeComma, ","},
    {TokenTypeIdent, "y"},
    {TokenTypeRParen, ")"},
    {TokenTypeLBrace, "{"},
    {TokenTypeIdent, "x"},
    {TokenTypePlus, "+"},
    {TokenTypeIdent, "y"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeRBrace, "}"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeLet, "let"},
    {TokenTypeIdent, "result"},
    {TokenTypeAssign, "="},
    {TokenTypeIdent, "add"},
    {TokenTypeLParen, "("},
    {TokenTypeIdent, "five"},
    {TokenTypeComma, ","},
    {TokenTypeIdent, "ten"},
    {TokenTypeRParen, ")"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeEOF, ""}
};
#define expected_tokens_2_len 13
Token expected_tokens_2[expected_tokens_2_len] = {
    {TokenTypeBang,	 "!"},
    {TokenTypeMinus,	 "-"},
    {TokenTypeSlash,	 "/"},
    {TokenTypeAsterisk,	 "*"},
    {TokenTypeInt,	 "5"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeInt,	 "5"},
    {TokenTypeLT,        "<"},
    {TokenTypeInt,	 "10"},
    {TokenTypeGT,	 ">"},
    {TokenTypeInt,	 "5"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeEOF,       ""},
};
#define expected_tokens_3_len 18
Token expected_tokens_3[expected_tokens_3_len] = {
    {TokenTypeIf,	 "if"},
    {TokenTypeLParen,	 "("},
    {TokenTypeInt,	 "5"},
    {TokenTypeLT,	 "<"},
    {TokenTypeInt,       "10"},
    {TokenTypeRParen,	 ")"},
    {TokenTypeLBrace,    "{"},
    {TokenTypeReturn,	 "return"},
    {TokenTypeTrue,      "true"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeRBrace,	 "}"},
    {TokenTypeElse,	 "else"},
    {TokenTypeLBrace,    "{"},
    {TokenTypeReturn,    "return"},
    {TokenTypeFalse,     "false"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeRBrace,    "}"},
    {TokenTypeEOF,       ""},
};
#define expected_tokens_4_len 9
Token expected_tokens_4[expected_tokens_4_len] = {
    {TokenTypeInt,	 "10"},
    {TokenTypeEq,	 "=="},
    {TokenTypeInt,	 "9"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeInt,       "10"},
    {TokenTypeNotEq,	 "!="},
    {TokenTypeInt,       "9"},
    {TokenTypeSemicolon, ";"},
    {TokenTypeEOF,       ""},
};

typedef struct TestInput {
    char *desc;
    char *input;
    Token* tokens;
    int tokens_len;
} TestInput;

void run_test(char* test_desc, Lexer *lexer, char *input, Token expected_tokens[], int expected_tokens_len)
{
    for (int i = 0; i < expected_tokens_len; ++i) {
	Token *token = next_token(lexer);
	assert(token->type == expected_tokens[i].type);
	if (token) free(token);
    }
    printf("%s passed ✓\n", test_desc);
}

void run_tests()
{
    TestInput test_inputs[5] = {
	{"test_0", input_0, expected_tokens_0, expected_tokens_0_len},
	{"test_1", input_1, expected_tokens_1, expected_tokens_1_len},
	{"test_2", input_2, expected_tokens_2, expected_tokens_2_len},
	{"test_3", input_3, expected_tokens_3, expected_tokens_3_len},
	{"test_4", input_4, expected_tokens_4, expected_tokens_4_len},
    };
    for (int i = 0; i < 5; ++i) {
	TestInput test_input  = test_inputs[i];
	Lexer *lexer = new_lexer(test_input.input);
	run_test(test_input.desc, lexer, test_input.input, test_input.tokens, test_input.tokens_len);
	if (lexer) free(lexer);
    }
    printf("all tests passed ✓✓✓");
}
