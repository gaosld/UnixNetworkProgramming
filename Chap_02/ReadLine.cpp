#include <unistd.h>
#include <errno.h>

static int cnt_read;
static char *p_read;
static char buf_read[1024];

static ssize_t MyRead(int fd, char *p_char)
{
    while(cnt_read <= 0)
    {
        cnt_read = read(fd, buf_read, sizeof(buf_read));
        if(cnt_read < 0)
        {
            if(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }
        else if(cnt_read == 0)
        {
            return 0;
        }
        else
        {
            p_read = buf_read;
        }
    }

    --cnt_read;
    *p_char = *p_read++;
    return 1;
}

ssize_t ReadLine(int fd, void *p_line, size_t maxlen)
{
    ssize_t n = 0;
    ssize_t n_read = 0;
    char c = 0;
    char *p_char = (char *)p_line;

    while(n < maxlen - 1)
    {
        n_read = MyRead(fd, &c);
        if(n_read < 0)
        {
            return -1;
        }
        else if(n_read == 0)
        {
            *p_char = 0;
            return n;
        }
        else
        {
            *p_char++ = c;
            ++n;
            if(c == '\n')
            {
                break;
            }
        }
    }
    *p_char = 0;
    return n;
}
