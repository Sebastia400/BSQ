/*
** EPITECH PROJECT, 2021
** BSQ_mio
** File description:
** find_bsq.c
*/

#include "./include/bsq_lib.h"

int check_size(char **map, int *information)
{
    int x = information[0];
    int y = information[1];
    int size_y = y + information[2];
    int size_x = x + information[2];

    while (y < size_y) {
        x = information[0];
        while (x < size_x) {
            if (map[y] == NULL || map[y][x] == 'o' || map[y][x] == '\0')
                return (1);
            x++;
        }
        y++;
    }
    return (0);
}

int *save_info(int *information)
{
    int i = 0;
    int *information2 = malloc(sizeof(int) * 4);

    while (i < 3){
        information2[i] = information[i];
        i++;
    }
    return (information2);
}

int *find_bsq(char **map)
{
    int *information1 = malloc(sizeof(int) * 4);
    int *information2 = malloc(sizeof(int) * 4);

    while (map[information2[1]] != NULL) {
        information2[0] = 0;
        information2[2] = 1;
        while (map[information2[1]][information2[0]] != '\0') {
            while (check_size(map, information2) == 0)
                information2[2]++;
            information2[2]--;
            if (information2[2] > information1[2])
                information1 = save_info(information2);
            else
                information2[2] = 1;
            information2[0]++;
        }
        information2[1]++;
    }
    free(information2);
    return (information1);
}
