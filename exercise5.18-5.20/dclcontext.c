#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <ctype.h>
#include "dclcontext.h"
#include "utils.h"

#define MAXTOKEN 100
#define EXPR_POINTER_TO " pointer to"
#define EXPR_FUNCTION_RETURN " function returning"
#define EXPR_ARRAY " array"
#define EXPR_OF " of"

enum DCLContext_token
{
	NAME = 1,
	PARENS,
	BRACKETS,
	POINTER_TO
};

struct DCLContext
{
	char *oridecl;
	char *decl;
	char name[MAXTOKEN];
	char type_specifier[MAXTOKEN];
	char type_qualifier[MAXTOKEN];
	char out[MAXLINE];
	char token[MAXLINE];
	size_t outlen;
	size_t outsz;
	int current_tokentype;
	int is_finalized;
};
static int DCLContext_dcl(DCLContext *);
static int DCLContext_dirdcl(DCLContext *);
static int DCLContext_is_finalized(DCLContext *);
static int DCLContext_next_tokentype(DCLContext *);
static int DCLContext_peek_tokentype(DCLContext *);
static int DCLContext_current_tokentype(DCLContext *);
static int DCLContext_resolve_specifiers(DCLContext *);

static const char *g_type_specifiers[] =
{
	"void",
	"char",
	"short",
	"int",
	"long",
	"float",
	"double",
	"signed",
	"unsigned"
};
static const size_t g_type_specifierssz =
	sizeof g_type_specifiers / sizeof *g_type_specifiers;
static const char *g_type_qualifiers[] =
{
	"const",
	"volatile"
};
static const size_t g_type_qualifierssz =
	sizeof g_type_qualifiers / sizeof *g_type_qualifiers;

static int DCLContext_current_tokentype(DCLContext *context)
{
	return context->current_tokentype;
}

static int DCLContext_next_tokentype(DCLContext *context)
{
	char *p;

	if (!context)
		return -1;

	p = context->token;

	while (*context->decl == ' ' || *context->decl == '\t')
		(context->decl)++;
	if (*context->decl == '(') {
		(context->decl)++;
		if (*context->decl == ')') {
			strcpy(context->token, "()");
			context->current_tokentype = PARENS;
			(context->decl)++;
		} else {
			context->current_tokentype = '(';
		}
	} else if (*context->decl == '[') {
		while (*context->decl) {
			*p++ = *context->decl;
			if (*context->decl == ']')
				break;
			(context->decl)++;
		}
		*p = '\0';
		(context->decl)++;
		context->current_tokentype = BRACKETS;
	} else if (isalpha(*context->decl)) {
		while (isalnum(*context->decl)) {
			*p++ = *context->decl;
			(context->decl)++;
		}
		*p = '\0';
		context->current_tokentype = NAME;
	} else {
		context->current_tokentype = *context->decl;
		if (*context->decl) {
			(context->decl)++;
		}
	}
	return context->current_tokentype;
}

static int DCLContext_peek_tokentype(DCLContext *context)
{
	int ret;
	char *decl;
	decl = context->decl;

	while (*decl == ' ' || *decl == '\t')
		decl++;
	if (*decl == '(') {
		decl++;
		if (*decl == ')') {
			ret = PARENS;
		} else {
			ret = '(';
		}
	} else if (*decl == '[') {
		ret = BRACKETS;
	} else if (isalpha(*decl)) {
		ret = NAME;
	} else {
		ret = *decl;
	}
	return ret;
}

static int DCLContext_dcl(DCLContext *context)
{
	int ns, ret, toktype;
	size_t len;

	if (!context)
		return -1;

	ns = 0;
	toktype = DCLContext_next_tokentype(context);
	while (toktype && toktype == '*') {
		toktype = DCLContext_next_tokentype(context);
		ns++;
	}
	ret = DCLContext_dirdcl(context);
	if (ret) {
		PRINT_ERROR("failed DCLContext_dirdcl");
		return -1;
	}
	len = strlen(EXPR_POINTER_TO);
	while (ns-- > 0) {
		if (context->outlen < context->outsz) {
			strcat(context->out, EXPR_POINTER_TO);
			context->outlen += len;
		} else {
			PRINT_ERROR("expression is to long to fit into output");
			return -1;
		}
	}
	return 0;
}

static int DCLContext_dirdcl(DCLContext *context)
{
	int type;
	size_t len;

	if (!context)
		return -1;

	if (DCLContext_current_tokentype(context) == '(') {
		DCLContext_dcl(context);
		if (DCLContext_current_tokentype(context) != ')') {
			PRINT_ERROR("missing ')'");
			return -1;
		}
	} else if (DCLContext_current_tokentype(context) == NAME) {
		strcpy(context->name, context->token);
	} else if (DCLContext_current_tokentype(context) != '\0') {
		PRINT_ERROR("expected name or (dcl)");
	}
	while ((type = DCLContext_next_tokentype(context)) == PARENS
		|| type == BRACKETS) {
		if (type == PARENS) {
			len = strlen(EXPR_FUNCTION_RETURN);
			if (context->outlen + len >= context->outsz) {
				PRINT_ERROR("not enough space in output buffer");
				return -1;
			}
			strcat(context->out, EXPR_FUNCTION_RETURN);
			context->outlen += len;
		} else {
			len = strlen(EXPR_ARRAY) + strlen(context->token)
				+ strlen(EXPR_OF);
			if (context->outlen + len >= context->outsz) {
				PRINT_ERROR("not enough space in output buffer");
				return -1;
			}
			strcat(context->out, EXPR_ARRAY);
			strcat(context->out, context->token);
			strcat(context->out, EXPR_OF);
			context->outlen += len;
		}
	}
	return 0;
}

static int DCLContext_is_finalized(DCLContext *context)
{
	if (!context)
		return 0;

	return !!context->is_finalized;
}

static int DCLContext_resolve_specifiers(DCLContext *context)
{
	int ret;
	size_t typespsz, typeqfsz, toklen;
	size_t tlen, qlen, maxtlen, maxqlen;
	size_t *plen, maxlen;
	const char **typesp, **typeqf;
	char *buf;

	ret = 0;
	tlen = 0;
	qlen = 0;
	maxtlen = sizeof(context->type_specifier);
	maxqlen = sizeof(context->type_qualifier);
	typesp = g_type_specifiers;
	typeqf = g_type_qualifiers;
	typespsz = g_type_specifierssz;
	typeqfsz = g_type_qualifierssz;

	while (NAME == DCLContext_peek_tokentype(context)) {
		DCLContext_next_tokentype(context);
		if (-1 < in_str_array(context->token, typesp, typespsz)) {
			buf = context->type_specifier;
			maxlen = maxtlen;
			plen = &tlen;
		} else if (-1 < in_str_array(context->token, typeqf, typeqfsz)) {
			buf = context->type_qualifier;
			maxlen = maxqlen;
			plen = &qlen;
		} else {
			context->decl -= strlen(context->token);
			break;
		}
		toklen = strlen(context->token);
		if (0 == *plen) {
			if ((*plen + toklen) >= maxlen) {
				PRINT_ERROR("not enough space!");
				ret = -1;
				break;
			}
			strcpy(buf, context->token);
			*plen += toklen;
		} else {
			if ((*plen + toklen + 1) >= maxlen) {
				PRINT_ERROR("not enough space!");
				ret = -1;
				break;
			}
			strcpy(buf + *plen, " ");
			strcpy(buf + *plen + 1, context->token);
			*plen += toklen + 1;
		}
	}

	return ret;
}

DCLContext *DCLContext_init(const char *decl)
{
	DCLContext *context;

	if (!decl)
		return NULL;

	context = malloc(sizeof *context);
	if (!context)
		return NULL;
	context->oridecl = malloc(strlen(decl) + 1);
	if (!context->oridecl) {
		free(context);
		return NULL;
	}
	strcpy(context->oridecl, decl);
	context->decl = context->oridecl;
	context->outlen = 0;
	context->outsz = sizeof context->out / sizeof *context->out;
	context->out[0] = '\0';
	context->is_finalized = 0;
	context->current_tokentype = -1;
	context->type_qualifier[0] = '\0';
	context->type_specifier[0] = '\0';
	return context;
}

int DCLContext_express(DCLContext *context)
{
	if (!context)
		return -1;
	if (context->is_finalized)
		return 0;
	DCLContext_resolve_specifiers(context);
	DCLContext_dcl(context);
	context->is_finalized = 1;
	return 0;
}

int DCLContext_copy_result(DCLContext *context, char *outbuf, size_t outbufsz)
{
	int i;
	size_t namelen, outlen, offset;
	size_t type_specifierlen, type_qualifierlen;

	if (!context || !outbuf || !outbufsz)
		return -1;
	if (!DCLContext_is_finalized(context))
		return -1;

	offset = 0;
	namelen = strlen(context->name);
	type_specifierlen = strlen(context->type_specifier);
	type_qualifierlen = strlen(context->type_qualifier);
	outlen = strlen(context->out);
	if (namelen + type_specifierlen + outlen + 3 >= outbufsz) {
		PRINT_ERROR("cannot copy result, output buffer not large enough");
		return -1;
	}
	for (i = 0; i < 7; i++) {
		switch (i) {
		case 0:
			memcpy(outbuf, context->name, namelen);
			offset += namelen;
			break;
		case 1:
			memcpy(outbuf + offset, ":", 1);
			offset += 1;
			break;
		case 2:
			memcpy(outbuf + offset, context->out, outlen);
			offset += outlen;
			break;
		case 3:
			memcpy(outbuf + offset, " ", 1);
			offset++;
			break;
		case 4:
			if (!type_qualifierlen)
				break;
			memcpy(outbuf + offset, context->type_qualifier,
				type_qualifierlen);
			offset += type_qualifierlen;
			memcpy(outbuf + offset, " ", 1);
			offset++;
			break;
		case 5:
			memcpy(outbuf + offset, context->type_specifier,
				type_specifierlen);
			offset += type_specifierlen;
			break;
		case 6:
			memcpy(outbuf + offset, "\0", 1);
			offset += 1;
			break;
		default:
			break;
		}
	}
	return 0;
}

void DCLContext_destroy(DCLContext *context)
{
	if (!context)
		return;
	free(context->oridecl);
	free(context);
}
