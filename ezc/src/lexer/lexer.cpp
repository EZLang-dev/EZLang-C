#include <ezc.h>
#include <cctype>
#include <vector>
#include <cstdio>
#include <iostream>
#include <cstring>

std::vector<ez_token_t> tokens;

void ez_lex_word();
void ez_lex_number();
void ez_lex_string();
void ez_add_token_fast(EZ_TOKEN_TYPE type);

int c;
const char* code;
int codeLength;

char peek(int a){
    if(c + a > codeLength) return 0;
    return code[c + a];
}

char current(){
    return peek(0);
}

ez_token* ez_lex(const char* string, int* tokenc){

    tokens = std::vector<ez_token_t>();

    c = 0;
    code = string;
    codeLength = strlen(string);

    while(current()){

        if(current() == ' ') {c++; continue;}
        if(current() == '\t') {c++; continue;}
        if(current() == '\n') {c++; continue;}
        if(current() == ';') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_NEWLINE); continue;}
        if(current() == '/' && peek(1) == '/') {while(current() != '\n') c++; c++; continue;}

        if(current() == '{') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_BRACKETS_OPEN); continue;}
        if(current() == '}') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_BRACKETS_CLOSE); continue;}

        if(current() == '(') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_PARENTHASIS_OPEN); continue;}
        if(current() == ')') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_PARENTHASIS_CLOSE); continue;}

        if(current() == ',') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_COMMA); continue;}
        if(current() == '.') {c++; ez_add_token_fast(EZ_TOKEN_TYPE_ACCESS); continue;}

        if(isalpha(current())){
            ez_lex_word();
            continue;
        }

        if(isdigit(current())){
            ez_lex_number();
            continue;
        }

        if(current() == '"'){
            ez_lex_string();
            continue;
        }

        if(current() == '<'){
            c++;
            if(current() == '-'){
                ez_add_token_fast(EZ_TOKEN_TYPE_SET);
                c++;
                continue;
            }
            ez_add_token_fast(EZ_TOKEN_TYPE_LESS_THAN);
        }

        std::cerr << "[" << c << "]ERROR: Unexpected char: " << current() << "(" << (int)current() << ")" << std::endl;
        c++;
    }

    *tokenc = tokens.size();
    return tokens.data();

}

void ez_add_token_fast(EZ_TOKEN_TYPE type) {
    tokens.push_back({type, nullptr});
}

void ez_lex_word(){
    char* word_name = (char*)malloc(256);
    int word_current = 0;
    while(isalnum(current())){
        word_name[word_current++] = current();
        c++;
    }
    tokens.push_back(ez_token {EZ_TOKEN_TYPE_WORD, word_name, true});
}

void ez_lex_number(){
    char* digit_string = (char*)malloc(256);
    int digit_current = 0;
    while(isalnum(current())){
        digit_string[digit_current++] = current();
        c++;
    }
    tokens.push_back(ez_token {EZ_TOKEN_TYPE_NUM, digit_string, true});
}

void ez_lex_string(){
    char* digit_string = (char*)malloc(256);
    int digit_current = 0;
    c++;
    while(current() != '"'){
        digit_string[digit_current++] = current();
        c++;
    }
    c++;
    tokens.push_back(ez_token {EZ_TOKEN_TYPE_STRING, digit_string, true});
}