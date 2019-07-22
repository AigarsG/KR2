#ifndef EXERCISE5_18_5_20_HEADER
#define EXERCISE5_18_5_20_HEADER

/**
 * @brief expresses provided declaration in words
 *
 * Accepts C declaration statement and converts it to declaration in words.
 * Saves result in provided buffer if buffer is large enough.
 * @code
 * char buf[512];
 * int ret = decl2text("int (*daytab)[13]", buf, sizeof buf / sizeof *buf);
 * printf("%s\n", buf);
 * @endcode
 * @param decl string of C declaration statement
 * @param outbuf array for saving result
 * @param outbufsz size of outbuf array
 * @return 0 on success, -1 on failure
 */
int decl2text(const char *decl, char *outbuf, size_t outbufsz);

#endif
