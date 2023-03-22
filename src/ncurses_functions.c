#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include "sdl_functions.h"
#include<ncurses.h>
#include<unistd.h>
//terminal
bool lose_game(WINDOW *win,int max_y , int max_x){
    refresh();
    getmaxyx(win,max_y,max_x);
    mvwprintw(win,max_y/2,max_x/2-6,"%s" , "YOU LOSE");
    wrefresh(win);
    return true;
}

void zero_array(int lines, int columns, int array[lines][columns]){
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            array[i][j] = 0;
        }
     }
}

void print_arrow(WINDOW *win, int max_x , int max_y, int type){
      if(type == 1){
          mvwprintw(win,max_y/2-1,max_x/2+1, "%d" , 1);
      }
      else if(type == 2){
          mvwprintw(win,max_y/2-1,max_x/2+1, "%d" , 2);
      }
      else if(type == 3){
          mvwprintw(win,max_y/2-1,max_x/2+1, "%d" , 3);
      }
      else{
          init_pair(3,COLOR_RED,COLOR_BLACK);
          wattron(win,COLOR_PAIR(3));
          mvwprintw(win,max_y/2-1,max_x/2, "%s" , "!!!");
      }
      wrefresh(win);
      wattroff(win,COLOR_PAIR(3));
}

bool lose_window_terminal(WINDOW *win, int WIDE, int HIGTH){
    bool run = true;
    int choices[2] = {1,0},j = 0, choice = 0;
    while (run)
    {
        for (int i = 0; i < 2; i++)
        {
            if(choices[0] == 1){
                wattron(win, A_REVERSE);
            }
            mvwprintw(win,HIGTH/2-1,WIDE/2-4,"RESTART");
            if(choices[0] == 1){
                wattroff(win,A_REVERSE);
            }
            else{
                wattron(win, A_REVERSE);
            }
            mvwprintw(win,HIGTH/2,WIDE/2-3,"Exit");
            if(choices[1] == 1){
                wattroff(win,A_REVERSE);
            }
            refresh();
        }
        // refresh();
        choice = wgetch(win);
        switch(choice)
        {
            case KEY_UP:
            choices[j] = 0;
            j--;
            if(j == -1) j = 0;
            choices[j] = 1;
            break;
            case KEY_DOWN:
            choices[j] = 0;
            j++;
            if(j == 2) j = 1;
            choices[j] = 1;
            break;
            case KEY_SPACE:
            if(choices[0] == 1){
                run = false;
                return true;
            }
            else{
                run = false;
                return false;
            }
            break;
            default:
            break;

        }
        wrefresh(win);
    }
    
}