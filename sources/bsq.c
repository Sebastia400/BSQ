/*
** EPITECH PROJECT, 2021
** BSQ
** File description:
** read_save.c
*/

#include "./../include/my_bsqlib.h"

int check_bsq(char **map, int *information)
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

int *save_information(int *information)
{
    int i = 0;
    int *information2 = malloc(sizeof(int) * 4);

    while (i < 3){
        information2[i] = information[i];
        i++;
    }
    return (information2);
}

int *find_square(char **map)
{
    int *information1 = malloc(sizeof(int) * 4);
    int *information2 = malloc(sizeof(int) * 4);

    while (map[information2[1]] != NULL) {
        information2[0] = 0;
        information2[2] = 1;
        while (map[information2[1]][information2[0]] != '\0') {
            while (check_bsq(map, information2) == 0)
                information2[2]++;
            information2[2]--;
            if (information2[2] > information1[2])
                information1 = save_information(information2);
            else
                information2[2] = 1;
            information2[0]++;
        }
        information2[1]++;
    }
    free(information2);
    return (information1);
}

char **draw_square (char **map, int *information)
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

int main (int ac, char **av)
{
    char *filepath = av[1];
    char **map = fs_save(filepath);
    int *information = malloc(sizeof(int) * 4);
    int i = 0;
    information = find_square(map);
    map = draw_square(map, information);
    while (map[i] != NULL) {
        write(1, map[i], my_strlen(map[i]));
        write(1, "\n", 1);
        i++;
    }
    free(information);
    free(map);
    return (0);
}
