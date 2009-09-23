#ifndef STRING_H_GUARD
#define STRING_H_GUARD

#include <string.h>


/*
 * The same as strrnstr, but this function will ignore the case of the
 * characters in the needle and haystack strings.
 *
 */
const char *
strrncasestr(
    const char *  haystack,     /*  The string to search                        */
    const char *  needle,       /*  The string to search for                    */
    size_t  n);                 /*  The maximum amount of characters to search  */


/*
 * Tries to locate the needle within the string, whose last character
 * is located at the memory location denoted by haystack, searching
 * at maximum n characters from haystack on backwards through the
 * string
 *
 * If the string is found, a pointer to its first occurance -- as seen
 * from haystack on backwards -- within the string is returned.
 * If the string is not found, NULL is returned.
 *
 * Does not include the terminating \0 in the search.
 *
 *  strrnstr("haystack", "yst", 3);  //=> NULL
 *  strrnstr("haystack", "yst", 8);  //=> pointer to the 'y' in "haystack"
 *  strrnstr("haystack", "a",   8);  //=> pointer to the last 'a' in "haystack"
 *
 **/
const char *
strrnstr(
    const char *  haystack,     /*  The string to search                        */
    const char *  needle,       /*  The string to search for                    */
    size_t        n);           /*  The maximum amount of characters to search  */


/*
 * The same as strnstr, but this function will ignore the case of the
 * characters in the needle and haystack strings.
 *
 */
const char *
strncasestr(
    const char *  haystack,     /*  The string to search                        */
    const char *  needle,       /*  The string to search for                    */
    size_t        n);           /*  The maximum amount of characters to search  */


/*
 * Tries to locate the given needle within the given haystack's first n
 * characters (or the whole string if strlen(haystack) < n).
 *
 * If the string is found, a pointer to its first occurance within
 * the string is returned.
 * If the string is not found, NULL is returned.
 *
 * Does not include the terminating \0 in the search.
 *
 *  strnstr("haystack", "sac", 3)  //=> NULL
 *  strnstr("haystack", "sac", 8)  //=> pointer to the 's' in "haystack"
 *  strnstr("haystack", "a",   8)  //=> pointer to the first 'a' in "haystack"
 *
 **/
const char *
strnstr(
    const char *  haystack,     /*  The string to search                        */
    const char *  needle,       /*  The string to search for                    */
    size_t        n);           /*  The maximum amount of characters to search  */


/*
 * Tries to locate the given character within the given string, while
 * ignoring the case of the character and the characters within the
 * string.
 *
 * If the character is found, a pointer to its first occurance within
 * the string is returned.
 * If the character is not found, NULL is returned.
 *
 * Does not include the terminating \0 in the search.
 **/
char *
strcasechr(
    const char *  string,       /*  The string to search         */
    int           character);   /*  The character to search for  */


#endif
