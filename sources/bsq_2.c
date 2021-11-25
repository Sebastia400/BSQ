/*
** EPITECH PROJECT, 2021
** BSQ
** File description:
** read_save.c
*/
#include "./../include/my_bsqlib.h"

int get_rows(int fd)
{
    char *buffer = malloc(sizeof(char) * 1);
    char *firstline = malloc(sizeof(char) * 10);
    int i = 0;
    int size = 1;

    size = read(fd, buffer, 1);
    while (buffer[0] != '\n' && isdigit(buffer[0])) {
        if (size != -1) {
            firstline[i] = buffer[0];
            i++;
            size = read(fd, buffer, 1);
        }
        else
            exit (84);
    }
    free(buffer);
    firstline[i] = '\0';
    if (!my_getnbr(firstline))
        exit (84);
    return (my_getnbr(firstline));
}

int fs_open_file(char const *filepath)
{
    if (open(filepath, O_RDONLY) != -1) {
        return (0);
    }
    else {
        exit (84);
    }
}

int  *fs_len_x_y(char const *filepath, int fd)
{
    int *x_y = malloc(sizeof(int) * 2 + 1);
    struct stat buf;

    stat(filepath, &buf);
    x_y[1] = get_rows(fd);
    x_y[0] = (buf.st_size / x_y[1]) - 1;
    if (x_y[1] == 1)
        x_y[0] -= 2;
    return (x_y);
}

char *fs_save2(int fd, int *x_y, char *x_y_axis)
{
    int x = 0;
    char *buffer = malloc(sizeof(char) * 1);

    while (x <= x_y[0]) {
        read(fd, buffer, 1);
        if ((buffer[0] != '.' && buffer[0] != 'o') && buffer[0] != '\n') {
            exit (84);
        }
        x_y_axis[x] = buffer[0];
        x++;
    }
    x_y_axis[x - 1] = '\0';
    return (x_y_axis);
}

char **fs_save(char const *filepath)
{
    int *x_y = NULL;
    char **x_y_axis = NULL;
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int y = 0;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        x_y = fs_len_x_y(filepath, fd);
        x_y_axis = malloc(sizeof(char *) * x_y[1] + 2);
        while (y < x_y[1]) {
            x_y_axis[y] = malloc(sizeof(char) * x_y[0] + 1);
            fs_save2(fd, x_y, x_y_axis[y++]);
        }
        x_y_axis[y] = NULL;
        free(buffer);
        close(fd);
    }
    free(x_y);
    return (x_y_axis);
}