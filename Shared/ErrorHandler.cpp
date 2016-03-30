#include "ErrorHandler.h"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <errno.h>

static void ErrorHandler(bool b_flag_errno, int i_errno, const char *csz_fmt, va_list list_param);

void ErrSys(const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(true, errno, csz_fmt, list_param);
    va_end(list_param);

    exit(1);
}

void ErrCont(const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(true, errno, csz_fmt, list_param);
    va_end(list_param);
}

void ErrDump(const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(true, errno, csz_fmt, list_param);
    va_end(list_param);
    abort();
    exit(1);
}

void ErrSys(int i_err_no, const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(true, i_err_no, csz_fmt, list_param);
    va_end(list_param);

    exit(1);
}

void ErrCont(int i_err_no, const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(true, i_err_no, csz_fmt, list_param);
    va_end(list_param);
}

void ErrExit(const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(false, 0, csz_fmt, list_param);
    va_end(list_param);
    exit(1);
}

void ErrMsg(const char *csz_fmt, ...)
{
    va_list list_param;

    va_start(list_param, csz_fmt);
    ErrorHandler(false, 0, csz_fmt, list_param);
    va_end(list_param);
}

void ErrorHandler(bool b_flag_errno, int i_errno, const char *csz_fmt, va_list list_param)
{
    char sz_error_msg[MAX_ERROR_INFO_LENGTH] = { 0 };

    vsnprintf(sz_error_msg, MAX_ERROR_INFO_LENGTH, csz_fmt, list_param);
    int n_msg_length = strlen(sz_error_msg);
    if(b_flag_errno)
    {
        snprintf(sz_error_msg + n_msg_length, MAX_ERROR_INFO_LENGTH - n_msg_length, ": %s", strerror(i_errno));
    }
    strcat(sz_error_msg, "\n");
    fflush(stdout);
    fputs(sz_error_msg, stderr);
    fflush(NULL);
}
