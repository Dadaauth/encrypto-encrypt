#include <string.h>

int check_file_extension(const char *filename)
{
    int len = strlen(filename);
    if (len < 5)
    {
        return 0;
    }
    return strcmp(filename + len - 4, ".enc") == 0;
}