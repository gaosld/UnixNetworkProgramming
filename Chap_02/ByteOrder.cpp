#include <cstdio>

int main(int argc, char **argv)
{
    union
    {
        short s_data;
        char c_data[2];
    }
    un_data;

    un_data.s_data = 0x0102;
    if(sizeof(short) == 2)
    {
        if(un_data.c_data[0] == 1 && un_data.c_data[1] == 2)
        {
            printf("Big Endian\n");
        }
        else if(un_data.c_data[0] == 2 && un_data.c_data[1] == 1)
        {
            printf("Little Endian\n");
        }
        else
        {
            printf("Unknown byte order\n");
        }
    }
    else
    {
        printf("sizeof(short)=%d", sizeof(short));
    }
    return 0;
}
