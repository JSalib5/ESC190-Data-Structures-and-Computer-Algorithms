#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

int main(void)
{
    int nterms;
    struct term *terms;
    read_in_terms(&terms, &nterms, "cities.txt");
    //int res = lowest_match(terms, nterms, "car");
    //int res2 = highest_match(terms, nterms, "car");
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "C");
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}