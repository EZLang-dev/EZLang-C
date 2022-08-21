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

int cx = 1;
int cy = 1;

char peek(int a){
    if(c + a > codeLength) return 0;
    return code[c + a];
}

char current(){
    return peek(0);
}

void step(int a){
    for(int i = 0; i < a; i++){
        c++;
        cx++;

        if(current() == '\n'){
            cx = 1;
            cy++;
        }
    }
}



ez_token* ez_lex(const char* string, int* tokenc){

    tokens = std::vector<ez_token_t>();

    c = 0;
    code = string;
    codeLength = strlen(string);

    while(current()){

        if(current() == ' ') {step(1); continue;}
        if(current() == '\t') {step(1); continue;}
        if(current() == '\n') {step(1); continue;}
        if(current() == ';') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_NEWLINE); continue;}
        if(current() == '/' && peek(1) == '/') {while(current() != '\n') step(1); step(1); continue;} // While we havent switched line, increace "c". Then we increase c once more to step onto the next line.

        if(current() == '{') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_BRACKETS_OPEN); continue;}
        if(current() == '}') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_BRACKETS_CLOSE); continue;}

        if(current() == '(') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_PARENTHASIS_OPEN); continue;}
        if(current() == ')') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_PARENTHASIS_CLOSE); continue;}

        if(current() == ',') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_COMMA); continue;}
        if(current() == '.') {step(1); ez_add_token_fast(EZ_TOKEN_TYPE_ACCESS); continue;}

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
            step(1);
            if(current() == '-'){
                ez_add_token_fast(EZ_TOKEN_TYPE_SET);
                step(1);
                continue;
            }
            ez_add_token_fast(EZ_TOKEN_TYPE_LESS_THAN);
        }

        std::cerr << "[ line: " << cy << ", col: " << cx << " ]\tERROR:\tUnexpected char: \"" << current() << "\"\t(" << (int)current() << ")" << std::endl;
        step(1);
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
        step(1);
    }
    tokens.push_back(ez_token {EZ_TOKEN_TYPE_WORD, word_name, true});
}

void ez_lex_number(){
    char* digit_string = (char*)malloc(256);
    int digit_current = 0;
    while(isalnum(current())){
        digit_string[digit_current++] = current();
        step(1);
    }
    tokens.push_back(ez_token {EZ_TOKEN_TYPE_NUM, digit_string, true});
}

void ez_lex_string(){
    char* digit_string = (char*)malloc(256);
    int digit_current = 0;
    step(1);
    while(current() != '"'){
        digit_string[digit_current++] = current();
        step(1);
    }
    step(1);
    tokens.push_back(ez_token {EZ_TOKEN_TYPE_STRING, digit_string, true});
}