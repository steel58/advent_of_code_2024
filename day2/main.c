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

        int* new_process = calloc(found_datapoints, sizeof(int));
        for (int ignore = 0; ignore <= found_datapoints; ignore++) {
            int safe = 1;
            int increasing = 0;
            int arr_len = found_datapoints;
            if (ignore != found_datapoints) {
                for (int i = 0; i < found_datapoints-1; i++) {
                    if (i >= ignore) {
                        new_process[i] = process[i+1];
                    } else {
                        new_process[i] = process[i];
                    }
                }
                arr_len = found_datapoints - 1;
            }

            for (int i = 1; i < arr_len; i++) {
                int current = new_process[i];
                int previous = new_process[i - 1];
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

                if (diff <= 0) {
                    safe = 0;
                    break;
                }

                if (diff > 3) {
                    safe = 0;
                    break;
                }
            }

            if (safe == 1) {
                total_safe += safe;
                break;
            }
        }
    }


    printf("Total safe reports: %d\n", total_safe);
    return 0;
}
