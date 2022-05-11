/*
** EPITECH PROJECT, 2021
** BSQ_mio
** File description:
** map_size.c
*/

#include "./include/bsq_lib.h"

int y_value(int fd)
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
        } else
            exit (84);
    }
    free(buffer);
    firstline[i] = '\0';
    if (!my_getnbr(firstline))
        exit (84);
    return (my_getnbr(firstline));
}

int  *get_x_y(char const *filepath, int fd)
{
    int *x_y = malloc(sizeof(int) * 2 + 1);
    struct stat buf;
    long max_size = 0;

    stat(filepath, &buf);
    x_y[1] = y_value(fd);
    x_y[0] = (buf.st_size / x_y[1]) - 1;
    if (x_y[1] == 1)
        x_y[0] -= 2;
    max_size = x_y[0] * x_y[1];
    if (max_size > 25000000)
        exit (84);
    return (x_y);
}
