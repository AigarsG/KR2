#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "utils.h"
#include "exercise6.02.h"

/*** INTERNAL DEFINES, ENUMS AND STRUCTS ***/
enum state
{
	ERROR = -1,
	START_OF_STATEMENT = 0,
	END_OF_STATEMENT,
	START_OF_COMMENT,
	END_OF_COMMENT,
	START_OF_WORD,
	END_OF_WORD,
	NON_BLANK,
	BLANK,
	STATE_CNT,
	STOP
};

/* TODO Create keyword context structure */
struct keyword_context
{
	char **input;
};

/*** INTERNAL FUNCTION SIGNATURES ***/
static enum state parse_input(const char *input, size_t n_sig_chars,
	Treenode *);
static enum state is_space(const char c);
static enum state start_of_statement(char **s, size_t n_sig_chars, Treenode *);
static enum state end_of_statement(char **s, size_t n_sig_chars, Treenode *);
static enum state start_of_comment(char **s, size_t n_sig_chars, Treenode *);
static enum state end_of_comment(char **s, size_t n_sig_chars, Treenode *);
static enum state start_of_word(char **s, size_t n_sig_chars, Treenode *);
static enum state end_of_word(char **s, size_t n_sig_chars, Treenode *);
static enum state non_blank(char **s, size_t n_sig_chars, Treenode *);
static enum state blank(char **s, size_t n_sig_chars, Treenode *);
static enum state ignore(char **s, size_t n_sig_chars, Treenode *);

/*** GLOBALS ***/
/* Each enum state is and index to corresponding state function */
static int (*g_state_functions[])(char *, size_t, Treenode *) =
{
	start_of_statement,
	end_of_statement,
	start_of_comment,
	end_of_comment,
	start_of_word,
	end_of_word,
	non_blank,
	blank,
};

/*** INTERNAL FUNCTION IMPLEMENTATIONS ***/
static int parse_input(const char *input, size_t n_sig_chars, Treenode *root)
{
	int ret;
	char *ptr;
	enum state current;

	if (!input || !n_sig_chars || !root)
		return -EINVAL;

	ret = 0;
	ptr = (char *) input;
	current_state = START_OF_STATEMENT;
	/*
	 * TODO
	 * iterate over input
	 * 	identify type keywords as start of variable declaration
	 *		if they are part of comment or define
	 *			ignore them until end of comment/define
	 *		if previous declaration was terminated by ';'
	 *			start new declaration
	 *		else
	 *			ignore declaration as syntax error
	 */
	while (STOP != current) {
		current = g_state_functions[current](&ptr, n_sig_chars, root);
		if (ERROR == current) {
			PRINT_ERROR("Experienced error on state transition");
			ret = -1;
			break;
		}
	}

	return ret;
}

static int is_space(const char c)
{
	return c == ' ' || c == '\t';
}

static int is_space_or_eol(const char c)
{
	return is_space(c) || c == '\n';
}

static int is_start_of_word(const char c)
{
	return isalpha(c) || c == '_';
}

static int end_of_comment(const char *s, int multiline_comment)
{
	if (!s)
		return 0;
	if (multiline_comment)
		return *s == '*' && *(s + 1) == '/';
	else
		return *s == '\n';
}

static enum state start_of_statement(char **s, size_t n_sig_chars, Treenode *root)
{
	char c;
	c = **s;

	if (is_space_or_eol(c))
		return BLANK;
	return NON_BLANK;
}

static enum state end_of_statement(char **s, size_t n_sig_chars, Treenode *root)
{
	/* last character is ';', advance to next one and signal the start */
	(*s)++;
	return START_OF_STATEMENT;
}

static enum state start_of_comment(char **s, size_t n_sig_chars, Treenode *root)
{
	int multiline_comment;

	multiline_comment = 0;
	if (**s == '/' && *(*s + 1) == '*')
		multiline_comment = 1;
	*s += 2;
	while (**s && !end_of_comment(*s, multiline_comment))
		(*s)++;
	if (!(**s))
		return STOP;
	else
		return END_OF_COMMENT;
}

static enum state end_of_comment(char **s, size_t n_sig_chars, Treenode *root)
{
	/* Advance past single line or multiline comment */
	if (**s == '\n')
		(*s)++;
	else
		*s += 2;
	if (**s == '\0')
		return STOP;
	if (is_space_or_eol(**s))
		return BLANK;
	return NON_BLANK;
}

static enum state start_of_word(char **s, size_t n_sig_chars, Treenode *root)
{
	size_t len;
	enum state ret;
	char *word, *tmp;
	Treenode *node;
	int ends_with_comma;

	/*
	 * Save in tree word consisting of first n_sig_chars or whole word if
	 * its length is less than n_sig_chars
	 */
	len = 0;
	tmp = *s;
	ret = END_OF_WORD;
	node = NULL;
	ends_with_comma = 0;
	while (!is_space_or_eol(*tmp)) {
		if (*tmp == ',') {
			ends_with_comma = 1;
			break;
		}
		tmp++;
		len++;
	}
	if (len > n_sig_chars)
		len = n_sig_chars;
	word = malloc(len + 1);
	if (!word) {
		PRINT_ERROR("failed to allocate memory");
		return ERROR;
	}
	memset(word, 0, len + 1);
	memcpy(word, *s, len);

	/* TODO determine if its a valid keyword or variable name
	node = Treenode_add(root, word);*/

	if (!node) {
		PRINT_ERROR("failed to add word '%s' to node", word);
		ret = ERROR;
	}
	free(word);

	return ret;
}

static enum state end_of_word(char **s, size_t n_sig_chars, Treenode *root)
{
	/* TODO */
}

static enum state non_blank(char **s, size_t n_sig_chars, Treenode *root)
{
	if (start_of_comment(*s))
		return START_OF_COMMENT;
	if (is_start_of_word(**s))
		return START_OF_WORD;
	if (is_space_or_eol(**s))
		return BLANK;

	PRINT_ERROR("invalid start of statement");
	return ERROR;
}

static enum state blank(char **s, size_t n_sig_chars, Treenode *root)
{
	while (is_space_or_eol(**s))
		(*s)++;
	return NON_BLANK;
}

void print_unique_variables(const char *input, FILE *outstream, size_t n_sig_chars)
{
	Treenode *variable_tree;

	if (!input || !outstream || !n_sig_chars) {
		PRINT_ERROR("invalid input");
		return;
	}

	variable_tree = Treenode_init();
	if (!variable_tree) {
		PRINT_ERROR("failed to initialize variable_tree");
	}

	if (parse_input(input, n_sig_chars, variable_tree) < 0) {
		PRINT_ERROR("failed to parse input, %s (%d)", strerror(errno),
			errno);
		Treenode_destroy(variable_tree);
		return;
	}

	Treenode_print(variable_tree, outstream);
	Treenode_destroy(variable_tree);
}
