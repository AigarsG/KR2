#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "exercise5.18-5.20.h"
#include "dclcontext.h"


int decl2text(const char *decl, char *outbuf, size_t outbufsz)
{
	int ret;
	DCLContext *context;

	ret = 0;
	context = DCLContext_init(decl);
	if (!context) {
		PRINT_ERROR("failed to allocate memory DCLContext_init");
		return -1;
	}
	do {
		ret = DCLContext_express(context);
		if (ret) {
			PRINT_ERROR("failed to express declaration '%s'", decl);
			break;
		}

		ret = DCLContext_copy_result(context, outbuf, outbufsz);
		if (ret) {
			PRINT_ERROR("expression is to long to fit into output");
			break;
		}

	} while (0);

	DCLContext_destroy(context);
	return 0;
}
