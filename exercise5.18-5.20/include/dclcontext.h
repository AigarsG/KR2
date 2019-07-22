#ifndef DCLCONTEXT_HEADER
#define DCLCONTEXT_HEADER

/*** Declaration context DCLContext type and API ***/
typedef struct DCLContext DCLContext;
DCLContext *DCLContext_init(const char *decl);
int DCLContext_express(DCLContext *);
int DCLContext_copy_result(DCLContext *, char *outbuf, size_t outbufsz);
void DCLContext_destroy(DCLContext *);

#endif
