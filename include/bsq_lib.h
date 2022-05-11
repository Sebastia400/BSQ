/*
** EPITECH PROJECT, 2021
** BSQ
** File description:
** read_save.c
*/

#ifndef BSQ_LIB_H_
#define BSQ_LIB_H_

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>

    int y_valye(int fd);
    int fs_open_file(char const *filepath);
    int  *get_x_y(char const *filepath, int fd);
    char *save_map2(int fd, int *x_y, char *x_y_axis);
    char **save_map(char const *filepath);
    int check_size(char **map, int *information);
    int *save_info(int *information);
    int *find_bsq(char **map);
    char **print_map (char **map, int *information);
    int my_strlen(char const *str);
    int my_getnbr(char const *str);

#endif
