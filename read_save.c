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
    printf("X: %d Y: %d\n", x_y[0], x_y[1]);
    return (x_y);
}

char **fs_save(char const *filepath)
{
    int *x_y = fs_len_x_y(filepath);
    char **x_y_axis = malloc(sizeof(char *) * x_y[1] + 2);
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int x = 0;
    int y = 0;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        while (y < x_y[1]) {
            printf("x_y: %d\n", x_y[0]);
            x_y_axis[y] = malloc(sizeof(char) * x_y[0] + 2);
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

    while (y < size_y) {
        x = information[0];
        while (x < size_x) {
            if (map[y] == NULL || map[y][x] == 'o' || map[y][x] == '\0') 
                return (1);
            x++;
        }
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

    information1[0] = 0;
    information1[1] = 0;
    information1[2] = 1;
    while (map[y] != NULL) {
        information2[0] = 0;
        information2[1] = y;
        information2[2] = 0;
        x = 0;
        while (map[y][x] != '\0') {
            while (check_bsq(map, information2) == 0) {
                information2[2]++;
            }
            printf("size2: %d\n", information2[2]);
            information2[2]--;
            //printf("X: %d Y: %d Inf1: %d Inf2: %d\n", information1[0], information1[1], information1[2], information2[2]);
            if (information2[2] > information1[2]) {
                printf("size1: %d < size2: %d\n", information1[2], information2[2]);
                information1[0] = x;
                information1[1] = y;
                information1[2] = information2[2];
            } else {
                information2[0] = x;
                information2[2] = 0;
            }
            x++;
        }
        y++;
    }
    free(information2);
    //information1[2] = information1[2] - 1;
    printf("X:%d \n", information1[0]);
    printf("Y:%d\n", information1[1]);
    printf("Size:%d\n", information1[2]);

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
    return(map);
}

int main ()
{
    
    char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_empty";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_filled";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_with_obstacles_25pc";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_with_obstacles_50pc";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_with_obstacles_75pc";   
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_empty";   
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_filled";   
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_100_100";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_200_200";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500_2";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500_3";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_empty";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_empty";
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_empty"; 
    
    char **map = fs_save(filepath);
    int *information = malloc(sizeof(int) * 4);
    int i = 0;
    information = find_square(map);
    map = draw_square(map, information);
    while (map[i] != NULL) {
        printf("%s", map[i]);
        i++;
    }
    printf("\n");
    free(information);
    free(map);
    return (0);
}