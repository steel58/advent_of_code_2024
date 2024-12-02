#include <stdio.h>
#include <stdlib.h>

void sort(int*, int);
int loc_diff(int*, int*, int);
int similarity_score(int*, int*, int);
int index_of(int*, int, int);
void increment(int*, int, int);
int get(int*, int, int);


int main() {
    printf("Running\n");
    char filepath[] = "input.txt";
    FILE* input = fopen(filepath, "r");
    if (input == NULL) {
        printf("FILE NOT FOUND");
        return -1;
    }

    int locs_size = 128;
    int found_locs = 0;
    int *locs1 = calloc(locs_size, sizeof(int));
    int *locs2 = calloc(locs_size, sizeof(int));

    if (locs1 == NULL || locs2 == NULL) {
        printf("Memory allocation failed");
        return -1;
    }
    int test1;
    int test2;

    while (fscanf(input, "%d %d", &locs1[found_locs], &locs2[found_locs]) > 0) {
        printf("Loc 1: %d\n", locs1[found_locs]);
        printf("Loc 2: %d\n", locs2[found_locs]);
        if (found_locs == locs_size -1) {
            locs_size += 128;
            locs1 = realloc(locs1, locs_size * sizeof(int));
            locs2 = realloc(locs2, locs_size * sizeof(int));
            if (locs1 == NULL || locs2 == NULL) {
                return -1;
            }
        }
        found_locs++;
    }

    fclose(input);

    sort(locs1, found_locs);
    sort(locs2, found_locs);

    int distance = loc_diff(locs1, locs2, found_locs);
    int sim_score = similarity_score(locs1, locs2, found_locs);

    printf("Distance is: %d\n", distance);
    printf("Similarity score is: %d\n", sim_score);

    free(locs1);
    free(locs2);
        
    return 0;
}

void sort(int* array, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                array[j] = array[j] ^ array[j+1];
                array[j + 1] = array[j] ^ array[j+1];
                array[j] = array[j] ^ array[j+1];
            }
        }
    }
}

int loc_diff(int* arr1, int* arr2, int len) {
    int result = 0;
    for (int i = 0; i < len; i++) {
        result += abs(arr1[i] - arr2[i]);
    }

    return result;
}

int similarity_score(int* arr1, int* arr2, int len) {
    int result = 0;
    int unique_nums = 0;
    int* value_count = calloc(len, sizeof(int));
    int* keys = calloc(len, sizeof(int));

    for (int i = 0; i < len; i++) {
        int idx = index_of(keys, arr2[i], unique_nums);
        if (idx == -1) {
            keys[unique_nums] = arr2[i];
            idx = unique_nums;
            unique_nums++;
        }

        increment(value_count, idx, unique_nums);
    }

    for (int i = 0; i < len; i++) {
        int idx = index_of(keys, arr1[i], unique_nums);
        int count = get(value_count, idx, unique_nums);
        result += count * arr1[i];
    }

    return result;
}

int index_of(int* keys, int key,int len) {
    for (int i = 0; i < len; i++) {
        if (keys[i] == key) {
            return i;
        }
    }
    return -1;
}

void increment(int* values, int key, int len) {
    if (key < len) {
        values[key]++;
    }
}
int get(int* values, int key, int len) {
    if (key >= len || key < 0) {
        return 0;
    }
    return values[key];
}
