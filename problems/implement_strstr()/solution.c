/**
 * Implement strStr().
 *
 * Given two strings needle and haystack, return the index of the first
 * occurrence of needle in haystack, or -1 if needle is not part of
 * haystack.
 */

typedef enum { FOUND, SEARCHING } search_status_t;

int strStr(char * haystack, char * needle){
    /* index of the first needle in haystack, or -1 if not found */
    int i_needle;

    /* status of the needle */
    /* initialize to SEARCHING to start searching */
    search_status_t status = SEARCHING;

    /* STRing in OFFset string */
    search_status_t strOff(char * h, char * n);

    /* loop through each character in the haystack, until FOUND */
    char * h;   /* storing pointer h */
    for ((h = haystack); ((*h) && (status != FOUND)); ++h) {
        status = strOff(h, needle);
    } /* end for (; ((*h) && (status != FOUND)); ) */

    /* if found */
    if (FOUND==status) {
        /* calculate the index from offsets as integers */
        /* h will be one character ahead */
        i_needle = (int)(h - haystack - 1);
    } /* end if (FOUND==status) */
    else {
        i_needle = -1;
    } /* end (FOUND==status) else */

    /* return the index found */
    return i_needle;
} /* end strStr(char * haystack, char * needle) */

/**
 * STRing in OFFset string
 * Returns FOUND if the needle is at the current haystack[0];
 * SEARCHING if not.
 */
search_status_t strOff(char * haystack, char * needle){
    /* initialize status to FOUND */
    /* go back to searching on first unlike character */
    /* however if all characters are like,
     * FOUND falls through to the callee */
    search_status_t status = FOUND;

    /* loop through each character in the remaining haystack
     * and the needle */
    char * h;   /* pointer to current haystack character */
    char * n;   /* pointer to current needle character */
    for (h = haystack, n = needle;
        ((*h) && (*n) && (status != SEARCHING));
        ++h, ++n
    ) {
        /* compare the characters */
        if ((*h) != (*n)) {
            status = SEARCHING;
        } /* end if ((*h) != (*n)) */
    } /* end for (; ((*h) && (*n) && (status != SEARCHING)); ) */

    /* still searching if needle did not finish looping */
    if (*n) {
        status = SEARCHING;
    } /* end if (*h) */

    /* return status found */
    return status;
} /* end strOff(char * haystack, char * needle) */
