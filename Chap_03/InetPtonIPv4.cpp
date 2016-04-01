#include <arpa/inet.h>
#include <errno.h>

int inet_pton_v4(int family, const char *csz_addr, void *p_addr)
{
    if(family == AF_INET)
    {
        if(inet_aton(csz_addr, (struct in_addr *)p_addr))
        {
            return 1;
        }
        return 0;
    }
    errno = EAFNOSUPPORT;
    return -1;
}

