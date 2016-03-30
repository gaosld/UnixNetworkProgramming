#include <cstring>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../Shared/ErrorHandler.h"

int main(int argc, char **argv)
{
    int fd_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd_listen < 0)
    {
        ErrSys("socket error");
    }

    struct sockaddr_in addr_server;
    memset(&addr_server, 0, sizeof(addr_server));
    addr_server.sin_family = AF_INET;
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_server.sin_port = htons(13);

    if(bind(fd_listen, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0)
    {
        ErrSys("bind error");
    }

    if(listen(fd_listen, 1024) < 0)
    {
        ErrSys("listen error");
    }

    char sz_buf[1024] = { 0 };
    while(1)
    {
        struct sockaddr_in addr_client;
        memset(&addr_client, 0, sizeof(addr_client));
        int fd_conn = accept(fd_listen, NULL, NULL);
        if(fd_conn < 0)
        {
            ErrSys("accept error");
        }
        time_t time_now = time(NULL);
        snprintf(sz_buf, 1024, "%.24s\r\n", ctime(&time_now));
        if(send(fd_conn, sz_buf, strlen(sz_buf), 0) < 0)
        {
            ErrSys("send error");
        }
        if(close(fd_conn) < 0)
        {
            ErrSys("close error");
        }
    }

    return 0;
}
