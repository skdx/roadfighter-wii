#ifdef _WIN32
#include "windows.h"
#endif

#include <stdio.h>
#include <stdarg.h>

#include "filehandling.h"

#ifdef KITSCHY_DEBUG_MEMORY
#include "debug_memorymanager.h"
#endif

FILE *fp = 0;

void output_debug_message(const char *fmt, ...)
{
#ifndef _WII
    char text[256];
    va_list ap;

    if (fmt == 0)
        return ;

    va_start(ap, fmt);
    vsprintf(text, fmt, ap);
    va_end(ap);

    if (fp == 0)
		fp = f1open("roadfighter.dbg", "w", USERDATA);

    fprintf(fp, text);
    fflush(fp);
#endif
} /* glprintf */




void close_debug_messages(void)
{
#ifndef _WII
    fclose(fp);
    fp = 0;
#endif
} /* close_debug_messages */
