/*
** EPITECH PROJECT, 2021
** BSQ
** File description:
** read_save.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>

int fs_open_file(char const *filepath)
{
    if (open(filepath, O_RDONLY) != -1) {
        printf("SUCCESS\n");
        return (0);
    }
    else {
        printf("FALIURE\n");
        return (1);
    }
}




int  *fs_len_x_y(char const *filepath)
{
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int *x_y = malloc(sizeof(int) * 2 + 1);
    int size = 1;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        size = read(fd, buffer, 1);
        x_y[0] = 0;
        x_y[1] = 0;
        while (buffer[0] != '\0' && size != 0) {
            x_y[0] = 0;
            while (buffer[0] != '\n' && size != 0) {
                size = read(fd, buffer, 1);

                x_y[0] += 1;
            }
            x_y[1] += 1;
            size = read(fd, buffer, 1);
            
        }
        free(buffer);
        close(fd);
    }
    printf("X= %d\nY= %d\n", x_y[0], x_y[1]);
    return (x_y);
}

char **fs_save(char const *filepath)
{
    int *x_y = fs_len_x_y(filepath);
    char **x_y_axis = malloc(sizeof(char *) * x_y[1] + 1);
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int x = 0;
    int y = 0;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        while (y < x_y[1]) {
            x_y_axis[y] = malloc(sizeof(char) * x_y[0] + 1);
            x = 0;
            while (x <= x_y[0]) {
                read(fd, buffer, 1);
                x_y_axis[y][x] = buffer[0];
                x++;
            }
            x_y_axis[y][x] = '\0';
            y++;
        }
        x_y_axis[y] = NULL;
        free(buffer);
        close(fd);
    }
    free(x_y);
    return (x_y_axis);
}

int check_bsq(char **map, int *information)
{
    int x = information[0];
    int y = information[1];
    int size_y = y + information[2];
    int size_x = x + information[2];
    printf("X: %d Y: %d SY: %d SX: %d\n", x, y, size_y, size_x);
    while (y <= size_y) {
        x = information[0];
        while (x <= size_x) {
            //printf(" hay: %c\n",map[y][x]);
            if (map[y][x] == 'o' || map[y][x] == '\0') {
                //printf("return 1\n");
                return (1);
            }
            x++;
            
        }
        //printf("\n");

        y++;
        
    }
    return(0);
}

int *find_square(char **map)
{
    int y = 0;
    int x = 0;
    int *information1 = malloc(sizeof(int) * 4);
    int *information2 = malloc(sizeof(int) * 4);
    int n = 0;
    information2[2] = 1;
    information1[0] = 0;
    information1[1] = 0;
    information1[2] = 1;

    
    //printf("%s\n", map[1]);
    while (map[y] != NULL) {
        information2[0] = 0;
        information2[1] = y;
        x = 0;
        while (map[y][x] != '\0') {
            while (check_bsq(map, information2) == 0) {
                //printf("ENTRA");
                //printf("info: %d", information2[2]);
                information2[2]++;
                //printf("??¿?¿");
            }
            
            if (information2[2] > information1[2]) {
                //printf("info2: %d\n", information2[2]);
                information1[0] = x - 1;
                information1[1] = y;
                information1[2] = information2[2];
            }
            else {
                information2[0] = x;
                information2[2] = 0;
            }
            //printf("X: %dY: %d\n", x, y);
            x++;
        }
        y++;
    }
    printf("infofinal: %d", information1[2]);
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
            map[y][x] = 'X';
            x++;
        }
        y++;
    }
    return(map);
}

int main ()
{
    char filepath[] = "map2.txt";
    char **map = fs_save(filepath);
    int *information = malloc(sizeof(int) * 4);
    int i = 0;
    //int information[] = {4, 4, 4};
    information = find_square(map);
    map = draw_square(map, information);
    //printf("infromation:%d %d %d\n", information[0], information[1], information[2]);
    while (map[i] != NULL) {
        printf("%s\n", map[i]);
        i++;
    }
    free(information);
    free(map);
    return (0);
}