#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"
#include "exercise4.03.h"


struct variable
{
	double value;
	int is_set;
};

static double *g_opr;
static size_t g_opr_sz;
static size_t g_opr_idx = 0;
static struct variable g_variable_values['z' - 'a'];


static int is_empty(void);
static void push(double f);
static double pop(void);


static int isvariable(const char *s)
{
	if (strlen(s) != 1)
		return 0;
	if (s[0] >= 97 && s[0] <= 122)
		return 1;

	return 0;
}

static int is_variable_assignment(const char *s)
{
	return (strlen(s) == 2 && (s[0] >= 'a' && s[0] <= 'z') && s[1] == '='); 
}

static int set_variable(const char *s)
{
	if (is_empty()) {
		fprintf(stderr, "error: stack empty\n");
		return -1;
	}

	int idx = s[0] - 97;
	g_variable_values[idx].value = pop();
	g_variable_values[idx].is_set = 1;

	return 0;
}

static int handle_variable(const char *s)
{
	int idx = s[0] - 97;
	if (!g_variable_values[idx].is_set) {
		fprintf(stderr, "error: variable '%c' has no value set\n", s[0]);
		return -1;
	}

	push(g_variable_values[idx].value);

	return 0;
}

static int is_empty(void)
{
	return g_opr_idx <= 0;
}

static void push(double f)
{
	if (g_opr_idx < g_opr_sz)
		g_opr[g_opr_idx++] = f;
	else
		fprintf(stderr, "error: stack full, can't push %g\n", f);
}

static double pop(void)
{
	if (!is_empty())
		return g_opr[--g_opr_idx];
	else {
		fprintf(stderr, "error: stack empty\n");
		return 0.0;
	}
}

static int last(double *retval)
{
	if (!is_empty()) {
		*retval = g_opr[g_opr_idx - 1];
		return 1;
	} else {
		fprintf(stderr, "error: stack empty\n");
		return -1;
	}
}

static int isnumber(const char *s)
{
	int i, ret = 0, infrac = 0;
	size_t len;

	if (s == NULL)
		return 0;

	len = strlen(s);
	i = 0;
	while (s[i] == '+' || s[i] == '-')
		i++;

	for (; i < len; i++) {
		if (s[i] == '.') {
			if (!infrac)
				infrac = 1;
			else {
				ret = 0;
				break;
			}
		} else if (!isdigit(s[i])) {
			ret = 0;
			break;
		} else {
			ret = 1;
		}
	}

	return ret;
}

static int do_opp(const char *s, double *retval)
{
	int ret = 0;
	double tmp1;

	if (!strcmp("+", s)) {
		push(pop() + pop());
	} else if (!strcmp("-", s)) {
		tmp1 = pop();
		push(pop() - tmp1);
	} else if (!strcmp("*", s)) {
		push(pop() * pop());
	} else if (!strcmp("/", s)) {
		tmp1 = pop();
		if (tmp1 != 0.0)
			push(pop() / tmp1);
		else {
			fprintf(stderr, "error: division by zero\n");
			ret = -1;
		}
	} else if (!strcmp("%", s)) {
		tmp1 = pop();
		if (tmp1 != 0.0)
			push(fmod(pop(), tmp1));
		else {
			fprintf(stderr, "error: modulo by zero\n");
			ret = -1;
		}
	} else if (!strcmp("top", s)) {
		ret = last(retval);
	} else if (!strcmp("dup", s)) {
		ret = last(&tmp1);
		if (ret > 0) {
			push(tmp1);
			ret = 0;
		}
	} else if (!strcmp("swp", s)) {
		double tmp2 = pop();
		tmp1 = pop();
		push(tmp2);
		push(tmp1);	
	} else if (!strcmp("clr", s)) {
		if (!g_opr_idx)
			ret = 1;
		else {
			while (g_opr_idx)
				pop();	
		}
	} else if (!strcmp("sin", s)) {
		push(sin(pop()));
	} else if (!strcmp("exp", s)) {
		push(exp(pop()));
	} else if (!strcmp("pow", s)) {
		tmp1 = pop();
		push(pow(pop(), tmp1));
	} else {
		fprintf(stderr, "Unknown command '%s'\n", s);
		ret = -1;
	}
	return ret;
}

int evaluate(char *expression, double *retval)
{
	int ret;
	size_t len = strlen(expression);
	char *component = NULL, ecpy[len];

	g_opr_sz = len;
	g_opr = calloc(g_opr_sz, sizeof *g_opr);
	if (g_opr == NULL) {
		fprintf(stderr, "error: failed to allocated memory to g_opr\n");
		return -1;
	}

	memcpy(ecpy, expression, len);
	ecpy[len] = '\0';

	component = strtok(ecpy, " \t\n");
	while (component) {
		if (isnumber(component)) {
			push(atof(component));
		} else if (is_variable_assignment(component)) {
			ret = set_variable(component);
			if (ret)
				break;
		} else if (isvariable(component)) {
			ret = handle_variable(component);
			if (ret)
				break;
		} else {
			ret = do_opp(component, retval);
			if (ret)
				break;
		}
		component = strtok(NULL, " \t\n");
	}

	if (!ret)
		*retval = pop();

	free(g_opr);

	return ret;
}