/*
** EPITECH PROJECT, 2021
** BSQ_mio
** File description:
** main.c
*/

#include "./include/bsq_lib.h"

int main (int ac, char **av)
{
    char *filepath = av[1];
    char **map = save_map(filepath);
    int *information = malloc(sizeof(int) * 4);
    int i = 0;

    information = find_bsq(map);
    map = print_map(map, information);
    while (map[i] != NULL) {
        write(1, map[i], my_strlen(map[i]));
        write(1, "\n", 1);
        i++;
    }
    free(information);
    free(map);
    return (0);
}
