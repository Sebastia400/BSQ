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

int get_rows(int fd)
{
    char *buffer = malloc(sizeof(char) * 1);
    char *firstline = malloc(sizeof(char) * 10);
    int i = 0;
    int size = 1;
    
    size = read(fd, buffer, 1);
    while (buffer[0] != '\n') {
        if(size != -1) {
            firstline[i] = buffer[0];
            i++;
            size = read(fd, buffer, 1);
        }
        else 
            exit (84);
    }
    free(buffer);
    firstline[i] = '\0';
    if(!atoi(firstline)) 
        exit (84);
    return (atoi(firstline));
}

int fs_open_file(char const *filepath)
{
    if (open(filepath, O_RDONLY) != -1) {
        return (0);
    }
    else {
        exit (84);
    }
}

int  *fs_len_x_y(char const *filepath)
{
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int *x_y = malloc(sizeof(int) * 2 + 1);
    int size = 1;
    int y = 0;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        x_y[0] = 0;
        x_y[1] = get_rows(fd);
        while (y < x_y[1]) {
            x_y[0] = 0;
            while (buffer[0] != '\n' && size != 0) {
                size = read(fd, buffer, 1);
                x_y[0] += 1;
            }
            y ++;;
            size = read(fd, buffer, 1);
            if (size == -1)
                exit (84);
        }
        free(buffer);
        close(fd);
    }
    return (x_y);
}

char *fs_save2(int fd, int *x_y, char *x_y_axis)
{
    int x = 0;
    char *buffer = malloc(sizeof(char) * 1);

    while (x <= x_y[0]) {
        read(fd, buffer, 1);
        if ((buffer[0] == '\n' || buffer[0] == '\0') && x != x_y[0]) {
            exit (84);
        }
        if ((buffer[0] != '.' && buffer[0] != 'o') && buffer[0] != '\n') {
            exit (84);
        }
        x_y_axis[x] = buffer[0];
        x++;
    }       
    x_y_axis[x - 1] = '\0';
    return (x_y_axis);
}

char **fs_save(char const *filepath)
{
    int *x_y = fs_len_x_y(filepath);
    char **x_y_axis = malloc(sizeof(char *) * x_y[1] + 2);
    char *buffer = malloc(sizeof(char) * 1);
    int fd;
    int y = 0;

    if (!fs_open_file(filepath)) {
        fd = open(filepath, O_RDONLY);
        get_rows(fd);
        while (y < x_y[1]) {
            x_y_axis[y] = malloc(sizeof(char) * x_y[0] + 2);
            fs_save2(fd, x_y, x_y_axis[y]);
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
    /*if(information1[0] > 0)
        information1[0] = information1[0] - 1;*/
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
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_empty";                       //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_filled";                    //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_with_obstacles_25pc";       //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_with_obstacles_50pc";       //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_34_137_with_obstacles_75pc";       //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_empty";                      //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_filled";                     //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_with_obstacles_25pc";        //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_with_obstacles_50pc";        //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_97_21_with_obstacles_75pc";        //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_100_100";                          //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_187_187_empty";                    //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_187_187_filled";                   //OK 
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_187_187_with_obstacles_25pc";      //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_187_187_with_obstacles_50pc";      //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_187_187_with_obstacles_75pc";      //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_200_200";                          //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500";                          //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500_2";                        //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_500_500_3";                        //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_1000_1000";                        //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_1000_1000_2";                      //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_2000_2000";                        //OK
    char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_5000_5000";                        //OK too slow
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_10000_10000";                      //OK BUT TOO SLOW 2:43min 
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_empty_corners";                    //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_filled_corners";                   //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_column_with_obstacles_25pc";   //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_column_with_obstacles_50pc";   //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_column_with_obstacles_75pc";   //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_empty_box";                    //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_empty_column";                 //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_empty_line";                   //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_filled_box";                   //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_filled_column";                //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_filled_line";                  //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_line_with_obstacles_25pc";     //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_line_with_obstacles_50pc";     //OK
    //char filepath[] = "./maps-intermediate/mouli_maps/intermediate_map_one_line_with_obstacles_75pc";     //OK

    char **map = fs_save(filepath);
    int *information = malloc(sizeof(int) * 4);
    int i = 0;
    information = find_square(map);
    map = draw_square(map, information);
    while (map[i] != NULL) {
        printf("%s\n",map[i]);
        i++;
    }
    free(information);
    free(map);
    return (0);
}