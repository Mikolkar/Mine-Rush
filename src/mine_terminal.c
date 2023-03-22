#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include "sdl_functions.h"
#include<ncurses.h>
#include<unistd.h>
int main(int argc , char *argv[]){
    level level_type = {
    .easy = {10, 20},
    .medium = {14, 20},
    .hard = {17, 20}
    };
    int columns = 0;
    if (argc == 1){
        printf("Invalid argument.\nTo correctly run the program please select one of the following options:\neasy, medium, hard.\n");
        return 0;
    }
    if(strcmp(argv[1], "easy") == 0){
        columns = level_type.easy[0];
    }
    else if (strcmp(argv[1], "medium") == 0)
    {
        columns = level_type.medium[0];
    }
    else if (strcmp(argv[1], "hard") == 0)
    {
        columns = level_type.hard[0];
    }

    // defining a variables
    int lines = 14, size_h = lines, space = 2, length = columns + columns * space - space , **field = create_field(lines,columns), **hidden = create_field(lines,columns);
    int max_x = 80, max_y = 24, middle_x, middle_y,x = 0, y = 0,ch, wynik = 0, *score = &wynik, lives = 3;
    
    bool run = true, new_map = false, first_click = false , game_status = true, running_time = false ,lose = false;
    char **showmap = create_showmap(lines,columns);
    fill_with_hash(lines,columns,showmap);
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    //set sreen size
    getmaxyx(stdscr, middle_y, middle_x);
    //creating a window
    int height_in = max_y/1.5,width_in = max_x/1.4, Height_up = max_y/4 , highlight[lines][columns];
    WINDOW *up_win = newwin(Height_up-1,width_in,middle_y/4-Height_up+1,middle_x/2 - width_in/2);
    WINDOW *in_win = newwin(height_in, width_in, middle_y/4, middle_x/2 - width_in/2);
    WINDOW *clock_win = newwin(3, 5, middle_y/4-3-1, middle_x/2 - width_in/2+2);
    int choice = 0, gap = width_in/2 - (columns + columns * space - space)/2,gap_cp = gap, flag = 0;
    if(has_colors()){
        start_color();
    }
    
    refresh();
    box(up_win,0,0);
    box(in_win,0,0);
    box(clock_win,0,0);
    
    mvwprintw(up_win,Height_up/2-1,width_in-14, "SCORE:");
    wrefresh(up_win);
    wrefresh(in_win);
    print_arrow(clock_win, 2,5,3);
    wrefresh(clock_win);
    
    keypad(in_win,TRUE);
    zero_array(lines,columns,highlight);
    highlight[0][0] = 1;

    while (run)
    {
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if(highlight[i][j] == 1) wattron(in_win, A_REVERSE);
                else{
                    if(lose == true && field[i][j] == -1){
                        showmap[i][j] = '*';
                    }
                    if((int)(showmap[i][j]-'0') >= 1 && (int)(showmap[i][j]-'0') <= 8){
                        init_pair(1,COLOR_CYAN,COLOR_BLACK);
                        wattron(in_win,COLOR_PAIR(1));
                    }
                    else if (showmap[i][j] == 'F' || showmap[i][j] == '*')
                    {
                        init_pair(2,COLOR_RED,COLOR_BLACK);
                        wattron(in_win,COLOR_PAIR(2));
                    }
                } 
                mvwaddch(in_win,i+1,j + gap ,showmap[i][j]); 
                wattroff(in_win,A_REVERSE);
                wattroff(in_win, COLOR_PAIR(1));
                wattroff(in_win, COLOR_PAIR(2));
                gap += 2;
            }
            gap = gap_cp;
        }
        refresh();
        wrefresh(in_win);
        if(lose == true){
            getch();
            bool restart = lose_window_terminal(in_win,width_in,height_in);
            if(restart == true){
                free_field(field,lines);
                free_field(hidden,lines);
                free_showmap(showmap,lines);
                clear();
                execvp(argv[0], argv);
                perror("execvp");
                exit(EXIT_FAILURE); 
            }
            endwin();
            return 0;
        }
        choice = wgetch(in_win);
        switch(choice)
        {
            case KEY_UP:
            highlight[y][x] = 0;
            y--;
            if(y == -1) y = 0;
            highlight[y][x] = 1;
            break;
            case KEY_DOWN:
            highlight[y][x] = 0;
            y++;
            if(y == lines) y = lines-1;
            highlight[y][x] = 1;
            break;
            case KEY_RIGHT:
            highlight[y][x] = 0;
            x++;
            if(x == columns) x = columns-1;
            highlight[y][x] = 1;
            break;
            case KEY_LEFT:
            highlight[y][x] = 0;
            x--;
            if(x == -1) x = 0;
            highlight[y][x] = 1;
            break;
            default:
            break;
            case KEY_SPACE:
            if(first_click == false){
                first_click = true;
                set_bombs_point(lines, columns, field, x,y,first_click);
                new_map = true;
                running_time = true;
            }
            showmap = show_cells_point(lines,columns,field,showmap,x,y);
            if(field[y][x] == -1){
                showmap[y][x] = '*';
                lives--;
                if(lives == 0){
                lose = lose_game(up_win,0,0);
                }
            }
            break;
        }
        if ((choice==(int)'F' || choice == (int)'f'))
        {
            if(showmap[y][x] == '#' || showmap[y][x] == '.') showmap[y][x] = 'F';
            else if(showmap[y][x] == 'F') showmap[y][x] = '#';
        }
        
        else if ((choice==(int)'G' || choice == (int)'g'))
        {
            game_status = check_last_line_point(lines,columns,field,showmap,score);
            remove_last_line_point(lines,columns,field,size_h,hidden,showmap);
            size_h--;
            if(size_h == 0){
                new_map = true;
                size_h = lines;
            }
        }
        if(new_map == true){
            set_bombs_point(lines, columns, hidden, 0,0,false);
            new_map = false;
        }
        if(game_status == false){
            lives--;
            game_status = true;
            if(lives == 0){
            lose = lose_game(up_win,0,0);
        }
        }
        print_arrow(clock_win, 2,5,lives);
        mvwprintw(up_win,Height_up/2-1,width_in-6, "%d" , *score);
        usleep(5000);
        box(up_win,0,0);
        box(in_win,0,0);
        box(clock_win,0,0);
        wrefresh(up_win);
        wrefresh(in_win);
        print_arrow(clock_win, 2,5,lives);
        wrefresh(clock_win);
    }
    free_field(field,lines);
    free_field(hidden,lines);
    free_showmap(showmap,lines);
    getch();
    endwin();
    return 0;
}