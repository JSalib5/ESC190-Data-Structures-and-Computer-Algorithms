#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

//part 1
int compare(const void* a, const void* b) {
    struct term* termA = (struct term*)(a);
    struct term* termB = (struct term*)(b);
    return (strcmp(termA->term, termB->term));
}

void read_in_terms(struct term** terms, int* pnterms, char* filename) {
    char line[200];
    FILE* fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);
    *terms = (struct term*)malloc(sizeof(struct term) * (*pnterms));
    for (int i = 0; i < *pnterms; i++) {
        fgets(line, sizeof(line), fp);
        (*terms + i)->weight = (double)(atoi(line));
        char* token = strtok(line, "\t");
        token = strtok(NULL, "\t");
        int j = 0;
        while (token[j] != '\n') {
            (*terms + i)->term[j] = token[j];
            j++;
        }
        (*terms + i)->term[j] = '\0';
    }
    fclose(fp);
    qsort(*terms, *pnterms, sizeof(struct term), compare);
}

//part 2 a
char* selector(struct term* terms, int len, char* res) {
    for (int i = 0; i < len; i++) {
        res[i] = (terms->term)[i];
    }
    res[len] = '\0';
    return res;
}

int lowest_match(struct term* terms, int nterms, char* substr) {
    int low = 0;
    int high = nterms - 1;
    int mid = (int)((high + low) / 2);
    int len = strlen(substr);
    char str[200];
    while (low <= high) {
        char* sel = selector(terms + mid, len, str);
        if (strcmp(sel, substr) != 0) {
            if (strcmp(substr, sel) > 0) {
                low = mid + 1;
            }
            if (strcmp(substr, sel) < 0) {
                high = mid - 1;
            }
            mid = (int)((low + high) / 2);
        }
        if (strcmp(sel, substr) == 0) {
            if (strcmp(selector(terms + mid - 1, len, sel), substr) == 0) {
                mid = mid - 1;
            }
            if (strcmp(selector(terms + mid - 1, len, sel), substr) != 0) {
                return mid;
            }
        }
    }
    return -1;
}

//part 2 b
int highest_match(struct term* terms, int nterms, char* substr) {
    int low = 0;
    int high = nterms - 1;
    int mid = (int)((high + low) / 2);
    int len = strlen(substr);
    char str[200];
    while (low <= high) {
        char* sel = selector(terms + mid, len, str);
        if (strcmp(sel, substr) != 0) {
            if (strcmp(substr, sel) > 0) {
                low = mid + 1;
            }
            if (strcmp(substr, sel) < 0) {
                high = mid - 1;
            }
            mid = (int)((low + high) / 2);
        }
        if (strcmp(sel, substr) == 0) {
            if (strcmp(selector(terms + mid + 1, len, sel), substr) == 0) {
                mid = mid + 1;
            }
            if (strcmp(selector(terms + mid + 1, len, sel), substr) != 0) {
                return mid;
            }
        }
    }
    return -1;
}

//part 3
int compareAns(const void* a, const void* b) {
    struct term* termA = (struct term*)(a);
    struct term* termB = (struct term*)(b);
    if (termA->weight > termB->weight) {
        return -1;
    }
    if (termA->weight < termB->weight) {
        return 1;
    }
    else {
        return 0;
    }
}

void autocomplete(struct term** answer, int* n_answer, struct term* terms, int nterms, char* substr) {
    int lowest_index = lowest_match(terms, nterms, substr);
    int highest_index = highest_match(terms, nterms, substr);
    if (lowest_index == -1 && highest_index == -1) {
        *n_answer = 0;
    } else{
        *n_answer = highest_index - lowest_index + 1;
        *answer = (struct term*)malloc(sizeof(struct term) * (*n_answer + 1));
        for (int i = lowest_index; i <= highest_index; i++) {
            strcpy((*answer + (i - lowest_index))->term, (terms + i)->term);
            (*answer + (i - lowest_index))->weight = (terms + i)->weight;
        }
        qsort(*answer, *n_answer, sizeof(struct term), compareAns);
    }
}