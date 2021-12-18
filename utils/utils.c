#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "utils.h"


static int shift_right(char *, int *, int, int);


static int shift_right(char *a, int *sz, int start_idx, int shift_by)
{
	int  i = *sz - 1;
	while (i >= start_idx) {
		a[i + shift_by] = a[i];
		i--;
	}
	*sz += shift_by;
	return 0;
}


int mygetline(char *line, int maxlen)
{
	int i = 0;
	char c;
	while ((i < maxlen - 1) && (c = getchar()) != EOF && c != '\n') {
		line[i++] = c;
	}
	if (c == '\n') {
		line[i++] = c;
	}
	line[i] = '\0';
	return i;
}


int shift(char *a, int *sz, int start_idx, int shift_by)
{
	if (shift_by <= 0) {
		return 1;
	}
	return shift_right(a, sz, start_idx, shift_by);
}


int shift_left(char *s, unsigned int *sz, unsigned int offset)
{
	assert(*sz > offset);
	unsigned int i;
	for (i = offset; i < *sz; i++) {
		s[i - offset] = s[i];
	}
	*sz -= offset;
	return 0;
}


unsigned int getbits(unsigned int x, unsigned int p, unsigned int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
}


void reverse(char s[], size_t sz)
{
	int c, i, j;
	for (i = 0, j = sz - 1; i < j; i++, j--) {
		c = s[i], s[i] = s[j], s[j] = c;
	}
}

void mlfgets(char *buf, size_t sz, FILE *fp)
{
	size_t len, total;
	char tmp[sz], line[sz];

	memset(buf, 0, sz);
	memset(tmp, 0, sizeof tmp);
	total = 0;
	while (fgets(line, sz, fp)) {
		len = strlen(line);
		if (total + len < sz) {
			memcpy(tmp + total, line, len);
			total += len;
		} else {
			return;
		}
	}

	memcpy(buf, tmp, sizeof tmp);
}

int in_str_array(const char *needle, const char *haystack[], size_t haystacksz)
{
	size_t i;

	if (needle) {
		for (i = 0; i < haystacksz; i++) {
			if (!strcmp(needle, haystack[i]))
				return i;
		}
	}

	return -1;
}

/*** Bit Operations ***/
void set_bit(unsigned int bitnr, unsigned long *addr)
{
	unsigned int osbits;

	osbits = sizeof(void *) * CHAR_BIT;
	addr += bitnr / osbits;

	*addr |= 1ul << (bitnr % osbits);
}

unsigned int get_bit(unsigned int bitnr, unsigned long *addr)
{
	unsigned int osbits;

	osbits = sizeof(void *) * CHAR_BIT;
	addr += bitnr / osbits;

	return *addr & 1ul << (bitnr % osbits) ? 1 : 0;
}


/*** CircularBuffer ***/
typedef struct CircularBuffer
{
	size_t size;
	char **data;
	char **start;
	char **end;
} CircularBuffer;

CircularBuffer *circular_buffer_create(size_t size)
{
	CircularBuffer *ret;

	if (size < 1)
		return NULL;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return NULL;

	/* +1 redundant size to simplify implementation */
	ret->size = size + 1;
	ret->data = (char **) calloc(ret->size, sizeof(*ret->data));
	if (!ret->data) {
		free(ret);
		return NULL;
	}
	ret->start = ret->data;
	ret->end = ret->data;

	return ret;
}

void circular_buffer_destroy(CircularBuffer *cbuf)
{
	if (cbuf) {
		circular_buffer_clear(cbuf);
		free(cbuf->data);
		free(cbuf);
	}
}

void circular_buffer_push(CircularBuffer *cbuf, const char *s)
{
	if (cbuf) {
		char *dup, **next;

		dup = malloc(strlen(s) + 1);
		if (!dup)
			return;
		strcpy(dup, s);
		/* Free value being overwritten */
		if (*cbuf->end)
			free(*cbuf->end);
		*cbuf->end = dup;

		next = cbuf->end + 1;
		if (next == cbuf->data + cbuf->size)
			next = cbuf->data;

		cbuf->end = next;
		if (cbuf->end == cbuf->start) {
			cbuf->start += 1;
		}
		if (cbuf->start == cbuf->data + cbuf->size)
			cbuf->start = cbuf->data;
	}
}

char *circular_buffer_pop(CircularBuffer *cbuf)
{
	char *ret, **next;
	ret = NULL;
	if (cbuf) {
		if (cbuf->start == cbuf->end)
			return NULL;
		ret = *cbuf->start;
		next = cbuf->start + 1;
		if (next == cbuf->data + cbuf->size)
			next = cbuf->data;
		cbuf->start = next;
	}
	return ret;
}

void circular_buffer_clear(CircularBuffer *cbuf)
{
	if (cbuf) {
		char **pp;

		for (pp = cbuf->data; pp < cbuf->data + cbuf->size; pp++) {
			free(*pp);
			*pp = NULL;
		}

		cbuf->start = cbuf->data;
		cbuf->end = cbuf->data;
	}
}

size_t circular_buffer_count(CircularBuffer *cbuf)
{
	size_t ret;
	ret = 0;
	if (cbuf) {
		char **start;
		start = cbuf->start;
		while (start++ != cbuf->end) {
			ret++;
			if (start == cbuf->data + cbuf->size)
				start = cbuf->data;
		}
	}
	return ret;
}


/*** Treenode ***/
struct Treenode {
	char *value;
	int count;
	struct Treenode *left;
	struct Treenode *right;
};

Treenode *Treenode_init()
{
	Treenode *ret = malloc(sizeof *ret);

	if (!ret)
		return NULL;
	ret->value = NULL;
	ret->count = 0;
	ret->left = NULL;
	ret->right = NULL;

	return ret;
}

void Treenode_destroy(Treenode *node)
{
	Treenode *right;

	if (!node)
		return;

	right = node->right;
	Treenode_destroy(node->left);
	free(node->value);
	free(node);
	Treenode_destroy(right);
}

Treenode *Treenode_add(Treenode *root, const char *string)
{
	/* TODO check if its possible to return added node or NULL to indicate
	failure */
	Treenode *ret;
	size_t stringlen;
	int cmp;

	if (!root) {
		ret = Treenode_init();
		if (!ret)
			return NULL;
	} else {
		ret = root;
	}

	stringlen = strlen(string) + 1;

	if (!ret->value) {
		ret->value = malloc(stringlen);
		if (!ret->value)
			return NULL;
		strcpy(ret->value, string);
		ret->count = 1;
	} else {
		cmp = strcmp(ret->value, string);
		if (cmp < 0) {
			ret->right = Treenode_add(ret->right, string);
		} else if (cmp > 0) {
			ret->left = Treenode_add(ret->left, string);
		} else
			ret->count += 1;
	}

	return ret;
}

int Treenode_count(Treenode *root, const char *string)
{
	int ret, cmp;

	ret = 0;

	if (!root)
		return ret;

	if (!string) {
		ret += Treenode_count(root->left, string);
		ret += root->count;
		ret += Treenode_count(root->right, string);
	} else {
		cmp = strcmp(string, root->value);
		if (cmp < 0) {
			ret = Treenode_count(root->left, string);
		} else if (cmp > 0) {
			ret = Treenode_count(root->right, string);
		} else {
			ret = root->count;
		}
	}
	return ret;
}

Treenode *Treenode_find(Treenode *root, const char *string)
{
	int cmp;

	if (string && root && root->value) {
		cmp = strcmp(string, root->value);
		if (cmp < 0) {
			return Treenode_find(root->left, string);
		} else if (cmp > 0)
			return Treenode_find(root->right, string);
		else {
			return root;
		}
	}

	return NULL;
}

char *Treenode_get_value(Treenode *node)
{
	if (!node)
		return NULL;
	return node->value;
}

void Treenode_print(Treenode *node, FILE *stream)
{
	FILE *target;
	if (!node)
		return;
	if (!stream)
		target = stdin;
	else
		target = stream;
	Treenode_print(node->left, stream);
	if (node->value)
		fprintf(target, "%s: %d\n", node->value, node->count);
	Treenode_print(node->right, stream);
}


/*** LinkedList ***/
struct node {
	struct node *next;
	int val;
};

struct LinkedList {
	struct node *head;
	struct node *tail;
};

LinkedList *LinkedList_create(void)
{
	LinkedList *ret = malloc(sizeof *ret);
	if (ret) {
		ret->head = NULL;
		ret->tail = NULL;
	}
	return ret;
}

void LinkedList_destroy(LinkedList *llist)
{
	struct node *tmp;
	if (llist) {
		while (llist->tail) {
			tmp = llist->tail;
			llist->tail = llist->tail->next;
			free(tmp);
		}
		free(llist);
	}
}

int LinkedList_add(LinkedList *llist, int val)
{
	int rc = 0;
	struct node *n;

	if (llist == NULL) {
		rc = EINVAL;
	} else if ((n = malloc(sizeof *n)) == NULL) {
		rc = ENOMEM;
	} else {
		n->val = val;
		n->next = NULL;
		if (llist->tail == NULL) {
			llist->head = llist->tail = n;
		} else {
			llist->head->next = n;
			llist->head = n;
		}
	}

	return rc;
}

int LinkedList_head(const LinkedList *llist, int *rval)
{
	int rc = ENODATA;

	if (!llist || !rval) {
		rc = EINVAL;
	} else {
		if (llist->head) {
			*rval = llist->head->val;
			rc = 0;
		}
	}

	return rc;
}

int LinkedList_tail(const LinkedList *llist, int *rval)
{
	int rc = 0;

	if (!llist || !rval) {
		rc = EINVAL;
	} else {
		if (llist->tail)
			*rval = llist->tail->val;
		else
			*rval = 0;
	}

	return rc;
}

