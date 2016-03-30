#ifndef SHARED_ERRORHANDLER_H_
#define SHARED_ERRORHANDLER_H_

#define MAX_ERROR_INFO_LENGTH 1024

//Get extra error info from errno
void ErrSys(const char *csz_fmt, ...);
void ErrCont(const char *csz_fmt, ...);
void ErrDump(const char *csz_fmt, ...);

//Provide error no
void ErrSys(int i_err_no, const char *csz_fmt, ...);
void ErrCont(int i_err_no, const char *csz_fmt, ...);

//No extra error info from errno
void ErrExit(const char *csz_fmt, ...);
void ErrMsg(const char *csz_fmt, ...);

#endif //SHARED_ERRORHANDLER_H_
