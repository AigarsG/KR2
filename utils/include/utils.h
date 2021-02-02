#ifndef UTILS_H
#define UTILS_H
#include <limits.h>

#define MAXLINE 1000
#define PRINT_ERROR(frm, ...)						\
	fprintf(stderr, "%s.%d:error: "frm"\n", __FUNCTION__, __LINE__,	\
		##__VA_ARGS__)

enum boolean {FALSE=0, TRUE};


int mygetline(char *, int);
int shift(char *, int *, int, int);
int shift_left(char *s, unsigned int *sz, unsigned int offset);
unsigned int getbits(unsigned int x, unsigned int p, unsigned int n);
void reverse(char s[], size_t sz);
void mlfgets(char *buf, size_t sz, FILE *fp);
int in_str_array(const char *needle, const char *haystack[], size_t haystacksz);


/*** CircularBuffer ***/
typedef struct CircularBuffer CircularBuffer;
CircularBuffer *circular_buffer_create(size_t size);
void circular_buffer_destroy(CircularBuffer *cbuf);
void circular_buffer_push(CircularBuffer *cbuf, const char *s);
char *circular_buffer_pop(CircularBuffer *cbuf);
void circular_buffer_clear(CircularBuffer *cbuf);
size_t circular_buffer_count(CircularBuffer *cbuf);


/*** Bitmap Operations ***/
#define ULONG_BITMAP_SIZE(bitcnt)	\
	((bitcnt) ? 1 + (bitcnt) / (sizeof(void *) * CHAR_BIT) : 0)
void set_bit(unsigned int bitnr, unsigned long *addr);
unsigned int get_bit(unsigned int bitnr, unsigned long *addr);


/*** Treenode ***/
typedef struct Treenode Treenode;
Treenode *Treenode_init();
void Treenode_destroy(Treenode *node);
Treenode *Treenode_add(Treenode *root, const char *string);
int Treenode_count(Treenode *root, const char *string);
Treenode *Treenode_find(Treenode *root, const char *string);
char *Treenode_get_value(Treenode *);
void Treenode_print(Treenode *, FILE *stream);


/*** LinkedList ***/
typedef struct LinkedList LinkedList;
LinkedList *LinkedList_create(void);
void LinkedList_destroy(LinkedList *);
int LinkedList_add(LinkedList *, int val);
int LinkedList_top(const LinkedList *, int *rval);
int LinkedList_bottom(const LinkedList *, int *rval);

#endif
