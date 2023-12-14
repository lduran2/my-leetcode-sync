/**
 * Canonical : https://github.com/lduran2/my-leetcode-sync/blob/master/problems/integer_to_roman/solution.c
 * Given an integer, convert it to a roman numeral
 * represented by seven different symbols: I, V, X, L, C, D and M.
 * Language  : C with Basic inline x86 Assembly/GNU assembly syntax
 * By        : Leomar Durán <https://github.com/lduran2>
 * For       : https://leetcode.com/problems/integer-to-roman/
 *
 * CHANGELOG :
 *  v1.0.1 - 2023-12-14t07:14R
 *      testing conversion table
 *
 *  v1.0.0 - 2023-12-14t06:25R
 *      testing character buffer
 */

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for malloc */

/**
 * Conversion table between integers and Roman numerals symbols.
 * Each row represents a conversion by repeated subtraction from
 * highest to lowest.
 * All cells are bytes so integer equivalents are represented as 2
 * bytes (for this reason, integers > 255 are represented in the
 * hexadecimal base).
 *
 * column 0: the # of rows.
 * column 1: high byte of integer equivalent of Roman numeral symbol.
 * column 2: low  byte of integer equivalent ... .
 * column 3: number of characters in Roman numeral symbol.
 * column 4...: each successive character of the Roman numeral symbol,
 * the number of which is stored in column 3.
 */
char const ROMAN_TABLE[]
  = {13, 0x3, 0xE8 /* 1000 */, 1, 'M',
         0x3, 0x84 /*  900 */, 2, 'C', 'M',
         0x1, 0xF4 /*  500 */, 1, 'D',
         0x1, 0x90 /*  400 */, 2, 'C', 'D',
         0,            100   , 1, 'C',
         0,             90   , 2, 'X', 'C',
         0,             50   , 1, 'L',
         0,             40   , 2, 'X', 'L',
         0,             10   , 1, 'X',
         0,              9   , 2, 'I', 'X',
         0,              5   , 1, 'V',
         0,              4   , 2, 'I', 'V',
         0,              1   , 1, 'I',
    }; /* end ROMAN_TABLE */

/**
 * The size of "MMMDCCCLXXXVIII" (3888) the longest number in [1..3999]
 * in Roman numerals symbols plus the null terminator.
 */
size_t const MAX_ROMAN_LEN = 16;

/**
 * Converts the integer $num to a Roman numeral.
 * This function creates the Roman numeral string.
 * @param num: int[1..3999] = to convert to Roman numerals
 * @return: array[2..16]<char> = $num in Roman numerals
 * @see #MAX_ROMAN_LEN
 * @see #addNumerals
 */ 
char* intToRoman(int num) {
    /* for adding Roman numerals */
    char *addNumerals(char *, char const *, int);
    /* buffer for roman numerals */
    char *roman = addNumerals(malloc(MAX_ROMAN_LEN), ROMAN_TABLE, num);
    return roman;
} /* end intToRoman(int) */

/**
 * Adds the numeral representation of the integer $num, translated
 * according to the given conversion @table character, to buffer @cbuf.
 * @param cbuf %rdi: char * = to contain $num as numerals
 * @param table %rsi: char const * = by which to convert $num
 * @param num %rdx: int = to convert and add to @cbuf
 * @return @cbuf
 * @see #intToRoman
 */
__attribute__((naked))
char *addNumerals(char *cbuf, char const *table, int num) {
    __asm__(
        ".extern addSymbol;"    /* for adding each numeral symbol */

        "push %rax;"    /* store %rax for use */
        /* dummy buffer */
        "movl $'Z, %eax;"   /* store Z in accumulator */

        /* for all 15 characters, counting down */
        "movl $14, %ecx;"
    "cbuf_loop:"
        "movb %al, (%rdi,%rcx);" /* character in accumulator to cbuf */
        "dec %rax;" /* next character */
        "loop cbuf_loop;"
    /* end cbuf_loop */
    
        "movl $('A - 1), %eax;"    /* accumulate from ('A' - 1) */

        /* for each symbol row in the conversion table */ 
        "movzw (%rsi), %rcx;" /* load the number of symbols */
    "numeral_table_loop:"
        "inc %rsi;" /* next symbol */
        "inc %rax;" /* increase accumulator */
        "loop numeral_table_loop;"
    /* end numeral_table_loop */

        "movb %al, (%rdi);"     /* accumulator to cbuf, expect "M" */
        "movb $0, 15(%rdi);"    /* null terminate */

        "pop %rax;" /* restore %rax */
        "ret;"
    );
} /* end addNumerals(char *, char const *, int) */

__attribute__((naked))
void addSymbol(char *cbuf, char const *row) {

} /* end addSymbol(char *, char const *) */
