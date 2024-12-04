#include <stdio.h>
#include <stdlib.h>

int main() {
    char filepath[] = "input.txt";
    FILE* infile = fopen(filepath, "r");

    if (infile == NULL) {
        printf("FILE NOT OPENED\n");
        fclose(infile);
        return -1;
    }

    char line[24];

    int prev;
    int current;
    int total_safe = 0;
    int offset;

    while (fscanf(infile, "%[^\n] ", line) > 0) {
        char* process_read = line;
        int found_datapoints = 0;
        int max_arr = 10;
        int* process = calloc(max_arr, sizeof(int));

        //Gather data from file and put it all in an array
        while (sscanf(process_read, "%d %n", &process[found_datapoints], &offset) > 0) {
            process_read += offset;
            if (found_datapoints == max_arr - 1) {
                max_arr += 5;
                process = realloc(process, max_arr * sizeof(int));
            }
            found_datapoints++;
        }

        int safe = 1;
        int dampener = 1;
        int increasing = 0;
        for (int i = 1; i < found_datapoints; i++) {
            int current = process[i];
            int previous = process[i - 1];
            if (increasing == 0) {
                if (current > previous) {
                    increasing = 1;
                } else if (previous > current) {
                    increasing = -1;
                } else {
                    safe = 0;
                    break;
                }
            }

            int diff = (current - previous) * increasing;

            if (diff == 0) {
                if (dampener == 1) {
                    dampener = 0;
                } else {
                    safe = 0;
                    break;
                }
            }

            if (diff > 3) {
                if (dampener == 1) {
                    if (i == 1) {
                        int next = process[i + 1];
                        int next_diff = abs(next - current);
                        if (next_diff > 3) {
                            dampener = 0;
                            process[i] = process[i - 1];
                        }
                    } else {
                        dampener = 0;
                        process[i] = process[i - 1];
                    }
                } else {
                    safe = 0;
                    break;
                }
            }

            if (diff < 0) {
                if (dampener == 1) {
                } else {
                    safe = 0;
                    break;
                }
            }
        }

        if (safe == 0) {
            printf("Unsafe: %s\n", line);
        }

        total_safe += safe;
    }


    printf("Total safe reports: %d\n", total_safe);
    return 0;
}
