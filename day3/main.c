#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filepath[] = "input.txt";
    FILE* in_file = fopen(filepath, "r");

    int part1_sum = 0;

    int part2_sum = 0;

    char line[3500];
    int mult = 1;
    char c;
    while (fgets(line, 3500, in_file) > 0) { 
        int len = strlen(line);
        char* input = line;
        char close;
        int offset = 0;
        int chars_read = 0;
        int op1 = 0;
        int op2 = 0;
        while (offset < len) {
        char doBuffer[8];
            if (mult == 1) {
                sscanf(input, "%7s", doBuffer);
                if (strncmp(doBuffer, "don't()", strlen(doBuffer)) == 0) {
                    mult = 0;
                }
            } else {
                sscanf(input, "%4s", doBuffer);
                if (strncmp(doBuffer, "do()", strlen("do()")) == 0) {
                    mult = 1;
                }
            }

            int scan = sscanf(input, "mul(%d,%d%[)]%n", &op1, &op2, &close, &chars_read);
            if (scan == 3) {
                part1_sum += op1 * op2;
                if (mult == 1) {
                    part2_sum += op1 * op2;
                }
                offset += chars_read;
                input += chars_read;
            } else {
                offset++;
                input++;
            }
            op1 = 0;
            op2 = 0;
        }

    }
    


    printf("Raw Sum: %d\n", part1_sum);
    printf("Cleaned Sum: %d\n", part2_sum);
}
