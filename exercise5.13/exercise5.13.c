#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "exercise5.13.h"


typedef struct Arg
{
	char id;
	void *val;
} Arg;

typedef struct Array
{
	size_t size;
	size_t nelements;
	Arg *elements;
} Array;

static Array *init_arg_array(size_t sz)
{
	Array *ret = calloc(1, sizeof(*ret));

	if (!ret)
		return ret;

	ret->size = sz;
	ret->elements = calloc(ret->size, sizeof(*ret->elements));
	if (!ret->elements) {
		free(ret);
		return NULL;
	}

	ret->nelements = 0;

	return ret;
}

static void free_arg_array(Array *a)
{
	if (a) {
		size_t i;
		for (i = 0; i < a->nelements; i++) {
			free(a->elements[i].val);
		}
		free(a->elements);
		free(a);
	}
}

static void add_arg_array(Array *a, char id, void *val)
{
	if (a->nelements < a->size) {
		Arg *parg = &(a->elements[a->nelements]);
		parg->id = id;
		parg->val = val;
		a->nelements += 1;
	}
}

static void parse_args(int argc, char **argv, Array *a)
{
	int i;

	if (argc > a->size) {
		Arg *relements = realloc(a->elements, argc);
		if (relements) {
			a->elements = relements;
			a->size = argc;
		} else {
			free_arg_array(a);
			return;
		}
	}

	for (i = 0; i < argc - 1; i++) {
		if (!strncmp("-n", argv[i], 3)) {
			int *val = malloc(sizeof(*val));
			if (!val) {
				return;
			}
			*val = strtol(argv[i+1], NULL, 10);
			if (*val > 100)
				*val = 100;
			add_arg_array(a, argv[i][1], (void *) val);
		}
	}
}

static Arg *get_arg_by_id(Array *args, char id)
{
	size_t i;
	for (i = 0; i < args->nelements; i++) {
		if (args->elements[i].id == id)
			return &(args->elements[i]);
	}
	return NULL;
}

static void tail(Array *args)
{
	int len, nval;
	char line[80];
	CircularBuffer *cbuf;

	Arg *arg = get_arg_by_id(args, 'n');
	if (!arg)
		nval = 10;
	else
		nval = *((int *) arg->val);

	/* create circular buffer of size *arg->val or default value */
	cbuf = circular_buffer_create(nval);
	if (!cbuf) {
		return;
	}

	/* preserve last n lines */
	while ((len = mygetline(line, sizeof line))) {
		circular_buffer_push(cbuf, line);
	}

	char *s;
	while ((s = circular_buffer_pop(cbuf)))
		printf("%s", s);

	circular_buffer_destroy(cbuf);
}


int main(int argc, char **argv)
{
	Array *args = init_arg_array(argc);
	if (!args)
		return -1;

	parse_args(argc, argv, args);

	tail(args);

	free_arg_array(args);
	return 0;
}
