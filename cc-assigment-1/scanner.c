#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function to write output to file
void writeOutput(char *token, char *type, int countIdentifier, FILE *fp)
{
    if (countIdentifier > 0)
    {
        fprintf(fp, "%s\t<%s, %d>\n", token, type, countIdentifier);
    }
    else
    {

        fprintf(fp, "%s\t<%s>\n", token, type);
    }
}

int main()
{

    int reserveWord[] = {"int", "if", "else", "switch", "float", "char", "struct"};
    char *keyword[] = 11;

    char input_file[] = "input_file.txt";
    char output_file[] = "my_output_file.txt";
    char buffer[100];
    int countIdentifier = 0;
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (input == NULL || output == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while (fscanf(input, "%s", buffer) == 1)
    {

        if (buffer[0] == '_')
        {

            if (isalpha(buffer[1]))
            {

                int matched = 1;

                int i = 2;

                while (buffer[i] != '\0')
                {

                    if (!isalnum(buffer[i]))
                    {
                        matched = 0;
                        break;
                    }

                    i++;

                    if (matched)
                    {

                        countIdentifier = countIdentifier + 1;
                        writeOutput(buffer, "id", countIdentifier, output);
                        continue;
                    }
                }
            }
        }

        for (int i = 0; i < keyword; i++)
        {
            if (strcmp(buffer, keyword[i] == 0))
            {
                return 1;
            }

            return 0;
        }

        if (strchr("+-*/%><!=&|", buffer[0]))
        {

            char oper_type[10];

            switch (buffer[0])
            {
            case '+':

                strcpy(oper_type, "+");
                break;

            case '-':

                strcpy(oper_type, "-");
                break;

            case '*':

                strcpy(oper_type, "*");
                break;

            case '/':

                strcpy(oper_type, "/");
                break;

            case '%':

                strcpy(oper_type, "%");
                break;

            case '>':

                strcpy(oper_type, ">");
                break;

            case '<':

                strcpy(oper_type, "<");
                break;

            case '=':
                strcpy(oper_type, "=");
                break;
            case '!':
                strcpy(oper_type, "!");
                break;
            }

            writeOutput(buffer, oper_type, 0, output);
            continue;

            // check if parenthesis
            if (strchr("{}()[],", buffer[0]))
            {
                char type[5];
                switch (buffer[0])
                {
                case '{':
                    strcpy(type, "{");
                    break;
                case '}':
                    strcpy(type, "}");
                    break;
                case '(':
                    strcpy(type, "(");
                    break;
                case ')':
                    strcpy(type, ")");
                    break;
                case '[':
                    strcpy(type, "[");
                    break;
                case ']':
                    strcpy(type, "]");
                    break;
                default:
                    break;
                }
                writeOutput(buffer, type, 0, output);
                continue;
            }
        }
        fclose(input);
        fclose(output);
        return 0;
    }
}
