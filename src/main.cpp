#include <stdio.h>
#include "ezc.h"

const char* program = "string a <- \"hi there\";int b <- 10;";

int main() {
    return ez_compile_string(program);;
}
