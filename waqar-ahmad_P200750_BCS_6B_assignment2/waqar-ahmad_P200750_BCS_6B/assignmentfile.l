%{
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int isKeyword(char buffer[]) {
    char keywords[32][10] = {"break", "continue",
                             "else", "float", "for",
                             "if", "int", "return", "struct", "switch",
                             "while"};
    int i, flag = 0;
    for (i = 0; i < 11; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    return flag; 
}
%}

%option noyywrap

%%

[ \t\n]+        /* skip whitespace */
[+*/%=<>!&-]    { cout << yytext << " ----> <" << yytext << '>' << endl; }
[{}()]          { cout << yytext << " ----> <" << yytext << '>' << endl; }
^#              { cout << yytext << " ----> <" << yytext << '>' << endl; }
[a-zA-Z][a-zA-Z0-9]* {
                    if (isKeyword(yytext) == 1)
                        cout << yytext << " ----> <" << yytext << '>' << endl;
                    else
                        cout << yytext << " <id> " << endl;
                }

%%

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        cout << "Error while opening the file" << endl;
        return 1;
    }

    yyrestart(file); // Set the input file for Flex

    yylex();

    

    fclose(file);
    return 0;
}
