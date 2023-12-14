/**
 * Canonical : https://github.com/lduran2/my-leetcode-sync/blob/master/problems/integer_to_roman/solution.c
 * Given an integer, convert it to a roman numeral
 * represented by seven different symbols: I, V, X, L, C, D and M.
 * Language  : C with Basic inline x86 Assembly/GNU assembly syntax
 * By        : Leomar Durán <https://github.com/lduran2>
 * For       : https://leetcode.com/problems/integer-to-roman/
 *
 * CHANGELOG :
 *  v1.0.2 - 2023-12-14t15:31R
 *      correct placement for null terminator
 *      fixed endianness of symbol values
 *
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
 * All cells are bytes so each integer equivalents are represented as
 * 2 bytes = 1 word, which is big endian according to the endianness
 * of LeetCode's implementation of gcc (check your own version).
 * (So for this reason, integers > 255 are represented in the
 * hexadecimal base).
 *
 * column 0: the # of rows.
 * column 1: low  byte of integer equivalent of Roman numeral symbol.
 * column 2: high byte of integer equivalent ... .
 * column 3: number of characters in Roman numeral symbol.
 * column 4...: each successive character of the Roman numeral symbol,
 * the number of which is stored in column 3.
 */
char const ROMAN_TABLE[]
  = {13, /* 1000 */ 0xE8, 0x3, 1, 'M',
         /*  900 */ 0x84, 0x3, 2, 'C', 'M',
         /*  500 */ 0xF4, 0x1, 1, 'D',
         /*  400 */ 0x90, 0x1, 2, 'C', 'D',
             100,           0, 1, 'C',
              90,           0, 2, 'X', 'C',
              50,           0, 1, 'L',
              40,           0, 2, 'X', 'L',
              10,           0, 1, 'X',
               9,           0, 2, 'I', 'X',
               5,           0, 1, 'V',
               4,           0, 2, 'I', 'V',
               1,           0, 1, 'I',
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

        "push %rdi;"            /* store %rdi for return */
        "push %rbx;"            /* store %rbx for use as symbol size */
        /* dummy buffer */
        "movl $'Z, %eax;"   /* store Z in accumulator */

        /* for all 15 characters, counting down */
        "movl $14, %ecx;"
    "cbuf_loop:"
        "movb %al, (%rdi,%rcx);"    /* character in accumulator to cbuf */
        "dec %rax;"                 /* next character */
        "loop cbuf_loop;"
        "movb %al, (%rdi,%rcx);" /* character in accumulator to cbuf */
    /* end cbuf_loop */
    
        /* for each symbol row in the conversion table */ 
        "movzb (%rsi), %rcx;"   /* load the number of symbols */
        "inc  %rsi;"            /* first symbol */
    "numeral_table_loop:"
        "movzw 0(%rsi), %rax;"  /* %rax := value of symbol */
        "movzb 2(%rsi), %rbx;"  /* %rbx :=  size of symbol */
        /* if (num < *table) then skip_numeral_symbol */
        "sub  %rax, %rdx;"
        "jl   skip_numeral_symbol;"
        //"call addSymbol;"     /* otherwise add the symbol */
        "add  %rbx, %rdi;"      /* advance cbuf */
        "jmp  numeral_table_loop;" 
        "jmp  continue_numeral_table_loop;"
    "skip_numeral_symbol:"
        "add  %rax, %rdx;"      /* recover %rdx from if-subtract */
        /* next symbol row */
        "add  %rbx, %rsi;"
        "add    $3, %rsi;"      /* value word length + size byte */
    "continue_numeral_table_loop:"
        "loop numeral_table_loop;"
    "end_numeral_table_loop:"

        "movb $0, (%rdi);"      /* null terminate */

        "pop %rbx;"             /* restore %rbx */
        "pop %rdi;"             /* restore %rdi for return */
        "mov  %rdi, %rax;"      /* return original %rdi */
        "ret;"
    );
} /* end addNumerals(char *, char const *, int) */

__attribute__((naked))
void addSymbol(char *cbuf, char const *row) {
    __asm__(

        "ret;"
    );
} /* end addSymbol(char *, char const *) */
