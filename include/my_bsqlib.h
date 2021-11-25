/*
** EPITECH PROJECT, 2021
** BSQ
** File description:
** read_save.c
*/


#ifndef MY_BSQLIB_H_
#define MY_BSQLIB_H_

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

int get_rows(int fd);
int fs_open_file(char const *filepath);
int  *fs_len_x_y(char const *filepath, int fd);
char *fs_save2(int fd, int *x_y, char *x_y_axis);
char **fs_save(char const *filepath);
int check_bsq(char **map, int *information);
int *save_information(int *information);
int *find_square(char **map);
char **draw_square (char **map, int *information);
int my_strlen(char const *str);
int my_getnbr(char const *str);
#endif