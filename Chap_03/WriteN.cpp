#include <unistd.h>
#include <errno.h>

ssize_t WriteN(int fd, const void *csz_buf, size_t n_bytes_to_write)
{
    ssize_t n_write = 0;
    size_t n_left = n_bytes_to_write;
    const char *csz_temp = (const char *)csz_buf;

    while(n_left > 0)
    {
        n_write = write(fd, csz_temp, n_left);
        if(n_write < 0 && (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK))
        {
            continue;
        }
        else
        {
            return -1;
        }
        n_left -= n_write;
        csz_temp += n_write;
    }
    return n_bytes_to_write;
}
