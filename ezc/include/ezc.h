#ifndef _EZC_MAIN_H
#define _EZC_MAIN_H


enum EZ_TOKEN_TYPE {
    EZ_TOKEN_TYPE_WORD,
    EZ_TOKEN_TYPE_STRING,
    EZ_TOKEN_TYPE_NUM,
    EZ_TOKEN_TYPE_SET,
    EZ_TOKEN_TYPE_LESS_THAN,
    EZ_TOKEN_TYPE_NEWLINE
};

typedef struct ez_token_t{
    enum EZ_TOKEN_TYPE type;
    char* value;
    bool malloc = false;
} ez_token;

ez_token* ez_lex(const char* string, int* tokenc);
int ez_compile_string(const char* string);

#endif