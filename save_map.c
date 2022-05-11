/*
** EPITECH PROJECT, 2021
** BSQ_mio
** File description:
** save_map.c
*/

#include "./include/bsq_lib.h"

int fs_open_file(char const *filepath)
{
    if (open(filepath, O_RDONLY) != -1) {
        return (0);
    } else {
        exit (84);
    }
}

char *save_map2(int fd, int *x_y, char *x_y_axis)
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

char **save_map(char const *filepath)
{
    int *x_y = NULL;
    char **x_y_axis = NULL;
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int y = 0;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        x_y = get_x_y(filepath, fd);
        x_y_axis = malloc(sizeof(char *) * x_y[1] + 2);
        while (y < x_y[1]) {
            x_y_axis[y] = malloc(sizeof(char) * x_y[0] + 1);
            save_map2(fd, x_y, x_y_axis[y++]);
        }
        x_y_axis[y] = NULL;
        free(buffer);
        close(fd);
    }
    free(x_y);
    return (x_y_axis);
}
