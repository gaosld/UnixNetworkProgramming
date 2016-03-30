#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../Shared/ErrorHandler.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        ErrExit("Usage: daytime <IP Address>");
    }

    int fd_sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if(fd_sock < 0)
    {
        ErrSys("socket error");
    }

    struct sockaddr_in6 addr_server;
    memset(&addr_server, 0, sizeof(addr_server));
    addr_server.sin6_family = AF_INET6;
    if(inet_pton(AF_INET6, argv[1], &addr_server.sin6_addr) <= 0)
    {
        ErrExit("inet_pton error(%s)", argv[1]);
    }
    addr_server.sin6_port = htons(13);

    if(connect(fd_sock, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0)
    {
        ErrSys("connect error");
    }

    char sz_buf[1024] = { 0 };
    int i_recv_bytes = 0;
    while((i_recv_bytes = recv(fd_sock, sz_buf, 1024, 0)) > 0)
    {
        sz_buf[i_recv_bytes] = 0;
        fputs(sz_buf, stdout);
    }

    if(i_recv_bytes < 0)
    {
        ErrSys("recv error");
    }

    return 0;
}
