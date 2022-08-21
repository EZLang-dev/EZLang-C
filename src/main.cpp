#include <stdio.h>
#include "ezc.h"

const char* program = "program {\n"
                      "\t// We use the arrows like ReCT does because it's cool.\n"
                      "\tstring name <- fetchname();\n"
                      "\twelcome(name);\n"
                      "\n"
                      "\treturn 0;\n"
                      "\n"
                      "}\n"
                      "\n"
                      "// The globals block is for defining global functions, variables etc. \n"
                      "// Any proper compiler should error function calls in the global scope, but it isn't a forbidden practice, although in the linking stage it becomes apparent that running code in globals barely works \n"
                      "\n"
                      "globals {\n"
                      "\n"
                      "    import \"stdio\"; // Import a standard library called stdio\n"
                      "    function welcome <- (string name) {\n"
                      "        printf(\"Hello, %s\\n\", name);\n"
                      "    }\n"
                      "    \n"
                      "    function fetchname <- () string {\n"
                      "        import \"console.ez\" // Import a header for some sort of console library in the current project or on system(project files prefered)\n"
                      "        return console.ask(\"What is your name? \") // Semicolons aren’t a must but should return a warning\n"
                      "    ";

int main() {
    return ez_compile_string(program);;
}
