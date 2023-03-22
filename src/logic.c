#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include "sdl_functions.h"
void remove_index(int size,int array[size],int index_to_rm){
    for (int i = index_to_rm; i < size-2; i++)
    {
        array[i] = array[i+1];
    }
}

void fill_with_hash(int lines, int columns, char **array){
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            array[i][j] = '#';
        }
    }
}

char** create_showmap(int lines, int columns){
    char **showmap = (char**)malloc(lines * sizeof(char*));
    for (int i = 0; i < lines; i++)
    {
        showmap[i] = (char*)malloc(columns * sizeof(char));
    }
    return showmap;
}

void free_showmap(char **showmap, int lines){
    for (int i = 0; i < lines; i++)
    {
        free(showmap[i]);
    }
    free(showmap);
}

int count_bombs_point(int lines,int columns,int **array,int y,int x){
    int suma = 0;
    if (y != 0)
    {
        if (x != 0)
        {
            if(array[y-1][x-1] == -1) suma++;
        }
        if (x != columns-1)
        {
            if (array[y-1][x+1] == -1) suma++;
        }
        if(array[y-1][x] == -1) suma++;
    }
    if (y != lines-1)
    {
        if (x != 0)
        {
            if(array[y+1][x-1] == -1) suma++;
        }
        if (x != columns-1)
        {
            if(array[y+1][x+1] == -1) suma++;
        }
        if(array[y+1][x] == -1) suma++;
    }
    if (x != 0)
    {
        if(array[y][x-1] == -1) suma++;
    }
    if (x != columns-1)
    {
        if(array[y][x+1] == -1) suma++;
    }
    return suma;
}

void set_bombs_point(int n, int m,int **field,int x_clicked,int y_clicked, bool first_click){
    int mine_probability = n*m * 0.19,size = n*m;
    int mines_list[size],random_num,bomb_index,num_line,num_column;
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        mines_list[i] = i;
    }
    for (int i = 0; i < mine_probability; i++)
    {
        random_num = rand() % size;
        bomb_index = mines_list[random_num];
        num_line = bomb_index / m;
        num_column = bomb_index % m;
        field[num_line][num_column] = -1;
        remove_index(size-1,mines_list,bomb_index);
        size--;
    }
    if(first_click == true){
        field[y_clicked][x_clicked] = 0;
        clear_after_first_click_point(n,m,field,x_clicked,y_clicked);
    } 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (field[i][j] != -1)
            {
                field[i][j] = count_bombs_point(n,m,field,i,j);
            }
        }
    }
}

int** create_field(int lines, int columns){
    int **showmap = (int**)malloc(lines * sizeof(int*));
    for (int i = 0; i < lines; i++)
    {
        showmap[i] = (int*)malloc(columns * sizeof(int));
    }
    return showmap;
}

void clear_after_first_click_point(int lines, int columns, int **array,int x_clicked, int y_clicked){
    int x = x_clicked, y = y_clicked;
    if (y != 0)
    {
        if (x != 0)
        {
            array[y-1][x-1] = 0;
        }
        if (x != columns-1)
        {
            array[y-1][x+1] = 0;
        }
        array[y-1][x] = 0;
    }
    if (y != lines-1)
    {
        if (x != 0)
        {
            array[y+1][x-1] = 0;
        }
        if (x != columns-1)
        {
            array[y+1][x+1] = 0;
        }
        array[y+1][x] = 0;
    }
    if (x != 0)
    {
        array[y][x-1] = 0;
    }
    if (x != columns-1)
    {
        array[y][x+1] = 0;
    }
}

void free_field(int **field, int lines){
    for (int i = 0; i < lines; i++)
    {
        free(field[i]);
    }
    free(field);
}

char** show_cells_point(int lines,int columns,int **field,char **showmap,int x_clicked,int y_clicked){
    int x = x_clicked, y = y_clicked;
    if(field[y][x] > 0 && field[y][x] <= 8){
        showmap[y][x] = field[y][x] + '0';
    }
    else if(field[y][x] == 0){
        showmap[y][x] = '.';
    }
    if(field[y][x] != 0){
        return showmap;
    }
    if (y != 0)
    {
        if(x != 0 && field[y-1][x-1] != -1 && showmap[y-1][x-1] != 'F' && showmap[y-1][x-1] != '.' 
        && ((int)showmap[y-1][x-1] < (int)'0' || (int)showmap[y-1][x-1] > (int)'8')){
            show_cells_point(lines,columns,field,showmap,x-1,y-1);
        }
        
        if(x != columns-1 && field[y-1][x+1] != -1 && showmap[y-1][x+1] != 'F' && showmap[y-1][x+1] != '.' 
        && ((int)showmap[y-1][x+1] < (int)'0' || (int)showmap[y-1][x+1] > (int)'8')){
            show_cells_point(lines,columns,field,showmap,x+1,y-1);
        }
        if(field[y-1][x] != -1 && showmap[y-1][x] != 'F' && showmap[y-1][x] != '.'
        && ((int)showmap[y-1][x] < (int)'0' || (int)showmap[y-1][x] > (int)'8')){
                show_cells_point(lines,columns,field,showmap,x,y-1);
            }
    }
    if (y != lines-1)
    {
        if(x != 0 && field[y+1][x-1] != -1 && showmap[y+1][x-1] != 'F'  && showmap[y+1][x-1] != '.'
        && ((int)showmap[y+1][x-1] < (int)'0' || (int)showmap[y+1][x-1] > (int)'8')){
            show_cells_point(lines,columns,field,showmap,x-1,y+1);
        }

        if(x != columns-1 && field[y+1][x+1] != -1 && showmap[y+1][x+1] != 'F'  && showmap[y+1][x+1] != '.'
        && ((int)showmap[y+1][x+1] < (int)'0' || (int)showmap[y+1][x+1] > (int)'8')){
            show_cells_point(lines,columns,field,showmap,x+1,y+1);
        }

        if(field[y+1][x] != -1 && showmap[y+1][x] != 'F'  && showmap[y+1][x] != '.'
        && ((int)showmap[y+1][x] < (int)'0' || (int)showmap[y+1][x] > (int)'8')){
                show_cells_point(lines,columns,field,showmap,x,y+1);
            }
    }

    if(x != 0 && field[y][x-1] != -1 && showmap[y][x-1] != 'F'  && showmap[y][x-1] != '.'
    && ((int)showmap[y][x-1] < (int)'0' || (int)showmap[y][x-1] > (int)'8')){
            show_cells_point(lines,columns,field,showmap,x-1,y);
    }

    if(x != columns-1 && field[y][x+1] != -1 && showmap[y][x+1] != 'F'  && showmap[y][x+1] != '.'
    && ((int)showmap[y][x+1] < (int)'0' || (int)showmap[y][x+1] > (int)'8')){
            show_cells_point(lines,columns,field,showmap,x+1,y);
    }
    return showmap;
    }

void remove_last_line_point(int lines, int columns, int **field,int size_cp, int **copy_array,char** showmap){
    for (int i = lines-1; i >= 1; i--)
    {
        for (int j = 0; j < columns; j++)
        {
            field[i][j] = field[i-1][j];
            showmap[i][j] = showmap[i-1][j];
        }
    }
    for (int i = 0; i < columns; i++)
    {
        field[0][i] = copy_array[size_cp-1][i];
        showmap[0][i] = '#';
    } 
}

bool check_last_line_point(int lines, int columns, int **field, char** showmap, int *score){
    bool game_status = true;
    for (int i = 0; i < columns; i++)
    {
        if(field[lines-1][i] == -1 && showmap[lines-1][i] == 'F'){
            (*score)++;
        }
        else if(field[lines-1][i] == -1 && showmap[lines-1][i] != 'F'){
            game_status = false;
        }
        else if(field[lines-1][i] != -1 && showmap[lines-1][i] == 'F'){
            game_status = false;
        }
    }
    return game_status;
}