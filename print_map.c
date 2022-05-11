/*
** EPITECH PROJECT, 2021
** BSQ_mio
** File description:
** print_map.c
*/

#include "./include/bsq_lib.h"

char **print_map(char **map, int *information)
{
    int x = information[0];
    int y = information[1];
    int size_y = y + information[2];
    int size_x = x + information[2];

    while (y < size_y) {
        x = information[0];
        while (x < size_x) {
            map[y][x] = 'x';
            x++;
        }
        y++;
    }
    return (map);
}
