#include <unistd.h>
#include <errno.h>

ssize_t ReadN(int fd, void *sz_buf, size_t n_bytes_to_read)
{
    ssize_t n_read = 0;
    size_t n_left = n_bytes_to_read;
    char *sz_temp = (char *)sz_buf;

    while(n_left > 0)
    {
        n_read = read(fd, sz_temp, n_left);
        if(n_read < 0)
        {
            if(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
            {
                n_read = 0;
                continue;
            }
            else
            {
                return -1;
            }
        }
        else if(n_read == 0)
        {
            break;
        }
        n_left -= n_read;
        sz_temp += n_read;
    }
    return n_bytes_to_read - n_left;
}
