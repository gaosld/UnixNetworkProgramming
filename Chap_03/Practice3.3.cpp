#include <arpa/inet.h>

int inet_pton_loose(int family, const char *csz_addr, void *p_addr)
{
    int i_ret = inet_pton(family, csz_addr, p_addr);
    if(i_ret == 0)
    {
        if(family == AF_INET)
        {
            return inet_aton(csz_addr, (struct in_addr *)p_addr);
        }
        else if(family == AF_INET6)
        {
            struct in_addr addr;
            if(inet_aton(csz_addr, &addr))
            {
                const char *csz_prev_v6 = "::ffff:";
                int len_addr_v6 = strlen(csz_addr) + strlen(csz_prev_v6);
                char *sz_addr_v6 = (char *)malloc(len_addr_v6 + 1);
                strcpy(sz_addr_v6, csz_prev_v6);
                strcat(sz_addr_v6, csz_addr);
                i_ret = inet_pton(family, sz_addr_v6, p_addr);
                free(sz_addr_v6);
            }
        }
    }
    return i_ret;
}

