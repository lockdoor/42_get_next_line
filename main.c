#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char    *file = "file2";
    int     fd = open(file, O_RDONLY);
    for (int i = 0; i < 6; i++){
        char *line = get_next_line(fd);
        printf ("%s", line);
        free (line);
    }

    close (fd);
    return (0);
}