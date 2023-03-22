#ifndef SDL_FUNCTIONS_H_INCLUDED
#define SDL_FUNCTIONS_H_INCLUDED
#include<SDL2/SDL.h>
#include<stdbool.h>
#include<ncurses.h>
#include<unistd.h>
#define DELAY 50000
#define KEY_SPACE (int)' '
//Structs
typedef struct level{
    int easy[2];
    int medium[2];
    int hard[2];
} level;
typedef struct numbers{
    SDL_Color colors[9];
    SDL_Surface *numbers_Suface[10];
    SDL_Texture *numbers_textures[10];
}numbers;
//functions GUI
SDL_Rect set_Rect(int x, int y, int hight, int width);
SDL_Texture *Create_texture(SDL_Renderer *renderer, const char *file);
int menu(SDL_Renderer *renderer, SDL_Texture *Bgtexture, SDL_Texture *start_tex, SDL_Texture *title,SDL_Texture *title_cp_tex, SDL_Rect start_rect , SDL_Rect title_rect);
int level_window(SDL_Renderer *renderer,SDL_Texture *Bgtexture, SDL_Texture *easy,SDL_Texture *medium,SDL_Texture *hard,SDL_Rect easy_rect, SDL_Rect medium_rect, SDL_Rect hard_rect);
void put_a_number(SDL_Renderer *renderer, SDL_Rect *obj_rect, numbers nums, char **showmap, int x, int y);
void display_hearts(SDL_Renderer *renderer,int lives, SDL_Texture *heart_tex, SDL_Rect heart_rect);
void display_score(SDL_Renderer *renderer,int *score, numbers white_nums, SDL_Texture *score_tex, SDL_Rect score_rect, int WIDE);
int lose_window(SDL_Renderer *renderer, SDL_Texture *restart_tex, SDL_Texture *exit_tex, SDL_Rect restart_rect,SDL_Rect exit_rect);
void show_bombs_sdl(SDL_Renderer *renderer, int lines, int columns, int **field, SDL_Texture *bomb_tex, SDL_Rect rectangle, int size, int space, int x);
//funcions Terminal
bool lose_game(WINDOW *win,int max_y , int max_x);
void zero_array(int lines, int columns, int array[lines][columns]);
void print_arrow(WINDOW *win, int max_x , int max_y, int type);
bool lose_window_terminal(WINDOW *win, int WIDE, int HIGTH);
//logic of game
void remove_index(int size,int array[size],int index_to_rm);
void fill_with_hash(int lines, int columns, char **array);
char** create_showmap(int lines, int columns);
void free_showmap(char **showmap, int lines);
void clear_after_first_click_point(int lines, int columns, int **array,int x_clicked, int y_clicked);
int count_bombs_point(int lines,int columns,int **array,int y,int x);
void set_bombs_point(int n, int m, int** field, int x_clicked, int y_clicked, bool first_click);
int** create_field(int lines, int columns);
void free_field(int **field, int lines);
char** show_cells_point(int lines,int columns,int **field,char **showmap,int x_clicked,int y_clicked);
void remove_last_line_point(int lines, int columns, int **field,int size_cp, int **copy_array,char** showmap);
bool check_last_line_point(int lines, int columns, int **field, char** showmap, int *score);
#endif 