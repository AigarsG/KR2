#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "utils.h"
#include "exercise5.17.h"


#define MAX_RULES 		(sizeof(unsigned long) * CHAR_BIT)
#define MAX_FIELD_RULE_PAIRS	3


enum rules
{
	RULE_N = 0,
	RULE_R,
	RULE_F,
	RULE_D,
	RULE_CNT,
};

typedef struct FieldRule
{
	unsigned int fieldnr;
	unsigned long rulebits[ULONG_BITMAP_SIZE(RULE_CNT)];
} FieldRule;
typedef int (*FieldRule_CompFunc)(void *s1, void *s2);
static void FieldRule_set_fieldnr(FieldRule *fr, unsigned int fieldnr);
static void FieldRule_set_rule(FieldRule *fr, char rule);
static FieldRule_CompFunc FieldRule_get_comp_func(FieldRule *);
static int FieldRule_comp(const char *s1, const char *s2, FieldRule *);

typedef struct SortingContext
{
	const char **array;
	size_t arraysz;
	FieldRule field_rules[MAX_FIELD_RULE_PAIRS];
	size_t field_rules_sz;
	size_t field_rules_cnt;
	short initialized;
	short sorted;
} SortingContext;
static void SortingContext_init(SortingContext *, const char **array,
	size_t arraysz, const char *rules);
static int SortingContext_parse_rules(SortingContext *, const char *rules);
static void SortingContext_sort(SortingContext *);
static int SortingContext_subsort(SortingContext *, int offset, size_t ruleidx);
static FieldRule *SortingContext_find_rule_by_fieldnr(SortingContext *,
	unsigned int fieldnr);

typedef struct StartEnd
{
	unsigned int start;
	unsigned int end;
} StartEnd;
static void StartEnd_get_startend_indexes(const char *line, FieldRule *,
	StartEnd *);

static int is_dord_chr(char c)
{
	return isalnum(c) || c == '\t' || c == ' ';
}

static int numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

static int mystrcmp(char *s1, char *s2, int case_insensitive, int directory_order)
{
	char tmp1, tmp2;

	if (!s1 && !s2)
		return 0;
	if (!s1 && s2)
		return -1;
	if (s1 && !s2)
		return 1;

	while (*s1) {
		if (directory_order) {
			if (!is_dord_chr(*s1)) {
				s1++;
				s2++;
				continue;
			}
		}
		if (case_insensitive) {
			tmp1 = tolower(*s1);
			tmp2 = tolower(*s2);
		} else {
			tmp1 = *s1;
			tmp2 = *s2;
		}
		if (tmp1 < tmp2)
			return -1;
		if (tmp1 > tmp2)
			return 1;
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

static int strcmp_case_insensitive(char *s1, char *s2)
{
	return mystrcmp(s1, s2, 1, 0);
}

static int strcmp_directory_order(char *s1, char *s2)
{
	return mystrcmp(s1, s2, 0, 1);
}

static int strcmp_directory_order_case_insensitive(char *s1, char *s2)
{
	return mystrcmp(s1, s2, 1, 1);
}

static void swap(void *v[], int i, int j)
{
	void *tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

static void myqsort(void *v[], int left, int right, FieldRule *fr)
{
	int i, last;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (FieldRule_comp(v[i], v[left], fr) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	myqsort(v, left, last - 1, fr);
	myqsort(v, last + 1, right, fr);
}


static void FieldRule_set_fieldnr(FieldRule *fr, unsigned int fieldnr)
{
	if (!fr)
		return;
	fr->fieldnr = fieldnr;
}

static void FieldRule_set_rule(FieldRule *fr, char rule)
{
	char r;
	r = tolower(rule);
	switch (r) {
	case 'n':
		set_bit(RULE_N, fr->rulebits);
		break;
	case 'r':
		set_bit(RULE_R, fr->rulebits);
		break;
	case 'f':
		set_bit(RULE_F, fr->rulebits);
		break;
	case 'd':
		set_bit(RULE_D, fr->rulebits);
		break;
	default:
		PRINT_ERROR("unknown rule '%c'", r);
		break;
	}
}

static FieldRule_CompFunc FieldRule_get_comp_func(FieldRule *fr)
{
	/*
	 * TODO based on bits in rules bitmap, select appropriate comparison
	 * function to use
	 */
	if (!fr)
		return (FieldRule_CompFunc) strcmp;

	if (get_bit(RULE_F, fr->rulebits) && get_bit(RULE_D, fr->rulebits)) {
		return (FieldRule_CompFunc) strcmp_directory_order_case_insensitive;
	} else if (get_bit(RULE_F, fr->rulebits)) {
		return (FieldRule_CompFunc) strcmp_case_insensitive;
	} else if (get_bit(RULE_D, fr->rulebits)) {
		return (FieldRule_CompFunc) strcmp_directory_order;
	} else if (get_bit(RULE_N, fr->rulebits)) {
		return (FieldRule_CompFunc) numcmp;
	}

	return (FieldRule_CompFunc) strcmp;
}

static int FieldRule_comp(const char *s1, const char *s2, FieldRule *fr)
{
	FieldRule_CompFunc compfunc;
	StartEnd se1, se2;
	char *f1, *f2;
	int cmp;

	memset(&se1, 0, sizeof se1);
	memset(&se2, 0, sizeof se2);
	if (!(compfunc = FieldRule_get_comp_func(fr)))
		PRINT_ERROR("failed to retrieve comp func");

	/*
	 * No field rule being applied, apply simple sort across whole length
	 * of strings
	 */
	if (!fr)
		return (*compfunc)((void *) s1, (void *) s2);

	/*
	 * Compare field of iterest. If field is not found in a line push the
	 * line toward end of array
	 */
	StartEnd_get_startend_indexes(s1, fr, &se1);
	StartEnd_get_startend_indexes(s2, fr, &se2);
	if (se1.start == se1.end) {
		if (se2.end > se2.start) {
			return 1;
		}
		return 0;
	} else if (se2.start == se2.end) {
		if (se1.end > se1.start) {
			return -1;
		}
		return 0;
	} else {
		if (!(f1 = calloc(se1.end - se1.start + 1, sizeof *f1))) {
			PRINT_ERROR("failed to allocate memory");
			return 0;
		}
		if (!(f2 = calloc(se2.end - se2.start + 1, sizeof *f2))) {
			PRINT_ERROR("failed to allocate memory");
			return 0;
		}
		strncpy(f1, s1 + se1.start, se1.end - se1.start);
		strncpy(f2, s2 + se2.start, se2.end - se2.start);
		cmp = (*compfunc)((void *) f1, (void *) f2);
		free(f1);
		free(f2);

		if (get_bit(RULE_R, fr->rulebits)) {
			if (cmp > 0)
				return -1;
			else if (cmp < 0)
				return 1;
			else
				return 0;
		}

		return cmp;
	}
}

static void StartEnd_get_startend_indexes(const char *line, FieldRule *fr,
	StartEnd *ret)
{
	char c;
	const char *tmp;
	unsigned int fieldnr;
	unsigned int field_start;
	short in_field;

	if (!line || !ret) {
		PRINT_ERROR("invalid arguments");
		return;
	}

	ret->start = 0;
	ret->end = 0;
	fieldnr = -1;
	in_field = 0;
	tmp = line;

	if (!fr) {
		ret->end = strlen(line);
		return;
	}

	while ((c = *tmp)) {
		if (c != ' ' && c != '\t' && c != '\n' && !in_field) {
			fieldnr++;
			in_field = 1;
			field_start = tmp - line;
		} else if (in_field && (c == ' ' || c == '\t' || c == '\n')) {
			in_field = 0;
			if (fieldnr == fr->fieldnr)
				break;
		}
		tmp++;
	}

	if (fieldnr == fr->fieldnr) {
		ret->start = field_start;
		ret->end = tmp - line;
	}
}

static int SortingContext_parse_rules(SortingContext *sctx, const char *rules)
{
	unsigned int fieldnr;
	FieldRule *fr;

	if (!sctx)
		return -1;

	if (!rules || !strncmp("", rules, 2))
		return 0;
	while (*rules && sctx->field_rules_cnt < sctx->field_rules_sz) {
		if (*rules != '-') {
			rules++;
			continue;
		}

		rules++;

		/* Determine for which field rules should be applied */
		fieldnr = 0;
		while (*rules >= '0' && *rules <= '9') {
			fieldnr += *rules - '0';
			rules++;
		}
		fr = SortingContext_find_rule_by_fieldnr(sctx, fieldnr);
		if (!fr) {
			fr = &sctx->field_rules[sctx->field_rules_cnt];
			sctx->field_rules_cnt += 1;
		}
		FieldRule_set_fieldnr(fr, fieldnr);

		/* Set rules for corresponding field */
		while (*rules && *rules != ' ' && *rules != '\t'
			&& *rules != '-') {
			FieldRule_set_rule(fr, *rules);
			rules++;
		}
	}

	return 0;
}

static void SortingContext_init(SortingContext *sctx, const char **array,
	size_t arraysz, const char *rules)
{
	if (!sctx || !array || !*array || !arraysz) {
		PRINT_ERROR("invalid arguments");
		return;
	}
	memset(sctx, 0, sizeof *sctx);
	sctx->field_rules_sz = sizeof sctx->field_rules / sizeof *sctx->field_rules;
	sctx->field_rules_cnt = 0;
	sctx->array = array;
	sctx->arraysz = arraysz;
	sctx->sorted = 0;
	if (!SortingContext_parse_rules(sctx, rules))
		sctx->initialized = 1;
}

static FieldRule *SortingContext_find_rule_by_fieldnr(SortingContext *sctx,
	unsigned int fieldnr)
{
	size_t i;

	if (!sctx)
		return NULL;

	for (i = 0; i < sctx->field_rules_cnt; i++) {
		if (sctx->field_rules[i].fieldnr == fieldnr)
			return &sctx->field_rules[i];
	}

	return NULL;
}

static int SortingContext_subsort(SortingContext *sctx, int offset, size_t ruleidx)
{
	FieldRule *fr;
	const char *line, **subarray;
	size_t i, subarraysz;
	int end_offset, end_found;

	if (!sctx || !sctx->initialized || sctx->sorted) {
		PRINT_ERROR("invalid sorting context or its state");
		return -1;
	}
	if (offset >= sctx->arraysz) {
		PRINT_ERROR("offset is larger than sctx->arraysz");
		return -1;
	}
	if (sctx->field_rules_cnt && ruleidx >= sctx->field_rules_cnt) {
		PRINT_ERROR("rule index is larger than number of field rules");
		return -1;
	}

	end_found = 0;
	end_offset = 0;
	fr = &sctx->field_rules[ruleidx];
	subarray = sctx->array + offset;
	subarraysz = sctx->arraysz - offset;

	/*
	 * Determine end in subarray considering fields on which previous rules
	 * where applied. Fields of first line of subarray that are already
	 * sorted should, together, be considered as compound id. For each
	 * consequtive line, test if these fields match. Line with a field that
	 * does not match already sorted field of the first line is the next line
	 * after the end line of subarray and also the starting line of subarray
	 * on next iteration.
	 */
	for (end_offset = 1; end_offset < subarraysz; end_offset++) {
		line = subarray[end_offset];

		for (i = 0; i < ruleidx; i++) {
			if (FieldRule_comp(*subarray, line,
				&sctx->field_rules[i])) {
				end_found = 1;
				break;
			}
		}

		if (end_found)
			break;
	}
	/* Sort subarray */
	myqsort((void **) subarray, 0, end_offset - 1, fr);

	return offset + end_offset;
}

static void SortingContext_sort(SortingContext *sctx)
{
	size_t i;
	int offset;

	if (!sctx || !sctx->initialized || sctx->sorted)
		return;

	if (!sctx->field_rules_cnt) {
		/* No sorting rules provided, apply default sorting */
		myqsort((void **) sctx->array, 0, sctx->arraysz - 1, NULL);
	} else {
		for (i = 0; i < sctx->field_rules_cnt; i++) {
			offset = 0;
			while (offset < sctx->arraysz - 1) {
				offset = SortingContext_subsort(sctx, offset, i);
				if (offset < 0) {
					PRINT_ERROR("failed SortingContext_subsort");
					return;
				}
			}
		}
	}

	sctx->sorted = 1;
}


int fieldsort(const char **array, size_t arraysz, const char *rules)
{
	SortingContext sctx;

	SortingContext_init(&sctx, array, arraysz, rules);
	SortingContext_sort(&sctx);

	return 0;
}
