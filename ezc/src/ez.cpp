#include <ezc.h>
#include <cstdio>
#include <stdlib.h>

int ez_compile_string(const char* string){
    int token_count;
    struct ez_token_t* tokens = ez_lex(string, &token_count);

    for(int i = 0; i < token_count; i++){
        if(tokens[i].value != nullptr)
            printf("TOKEN: %s, %s\n", EZ_TOKEN_TYPE_names[tokens[i].type], tokens[i].value);
        else
            printf("TOKEN: %s\n", EZ_TOKEN_TYPE_names[tokens[i].type]);
        if(tokens[i].malloc) free(tokens[i].value);
    }

    return 0;
}