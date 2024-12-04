#include <stdio.h>
#include <stdlib.h>

int main() {
    char filepath[] = "input.txt";
    FILE* in_file = fopen(filepath, "r");

    int sum = 0;

    int op1;
    int op2;

    char test_string[100];
    char c;
    int scanned = fscanf(in_file, "%[^m]", test_string);
    int more_chars = fscanf(in_file, "%c", &c);
    printf("%s\n", test_string);
    while (fscanf(in_file, "ul(%d,%d)", &op1, &op2) > 0 || scanned > 0 || more_chars > 0) {
        printf("%d, %d\n", op1, op2);
        if (op1 > 999 || op2 > 999) {
            fscanf(in_file, "%[^m]", test_string);
            continue;
        }

        scanned = fscanf(in_file, "%[^m]", test_string);
        more_chars = fscanf(in_file, "%c", &c);
        printf("%s\n%c\n", test_string, c);
        //sum++;
        sum += op1 * op2;
        op1 = 0;
        op2 = 0;
    }


    printf("Found output was: %d\n", sum);
}
