#include <cstring>
#include <cstdio>
#include <errno.h>
#include <netinet/in.h>

const char *inet_ntop_v4(int family, const void *p_addr, char *sz_addr, size_t length)
{
    if(family == AF_INET)
    {
        const uint8_t *p_temp = (const uint8_t *)p_addr;
        char sz_temp[INET_ADDRSTRLEN] = { 0 };
        snprintf(sz_temp, sizeof(sz_temp), "%d.%d.%d.%d", p_temp[0], p_temp[1], p_temp[2], p_temp[3]);
        if(strlen(sz_temp) >= length)
        {
            errno = ENOSPC;
            return NULL;
        }
        strcpy(sz_addr, sz_temp);
        return sz_addr;
    }
    errno = EAFNOSUPPORT;
    return NULL;
}

