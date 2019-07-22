#ifndef EXERCISE5_17_HEADER
#define EXERCISE5_17_HEADER

/**
 * @brief Sort array of strings according to passed sorting rules
 * @desc Sort array of strings according to passed sorting rules. Rules is a
 *   string in form "[-[FIELD_NUMBER][nrfd]]*" (ex. -1 -0nr). If no rules
 *   are provided, comparison will default to simple string comparison.
 *   If FIELD_NUMBER is not provided, it will default to first field of line.
 * @param array array of lines
 * @param arraysz size of array
 * @param rules string of rules
 */
int fieldsort(const char **array, size_t arraysz, const char *rules);

#endif
