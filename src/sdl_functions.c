#include <stdio.h>
#include <stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>
#include "sdl_functions.h"
#include<SDL2/SDL_image.h>
//gui

SDL_Rect set_Rect(int x, int y, int hight, int width){
    SDL_Rect object;
    object.x = x;
    object.y = y;
    object.h = hight;
    object.w = width;
    return object;
}

SDL_Texture *Create_texture(SDL_Renderer *renderer, const char *file){
    SDL_Surface *img = IMG_Load(file);
    SDL_Texture *img_texture = SDL_CreateTextureFromSurface(renderer,img);
    SDL_FreeSurface(img);
    return img_texture;
}

int menu(SDL_Renderer *renderer, SDL_Texture *Bgtexture, SDL_Texture *start_tex, SDL_Texture *title,SDL_Texture *title_cp_tex, SDL_Rect start_rect , SDL_Rect title_rect) {
    bool is_menu = true;
    int result;
    SDL_Event event;
    int cord_x, cord_y, mouse_state;
    while (is_menu) {
        SDL_RenderCopy(renderer,Bgtexture,0,0);
        SDL_RenderCopy(renderer,title_cp_tex,0,&title_rect); 
        SDL_RenderCopy(renderer,title,0,&title_rect);   
        SDL_RenderCopy(renderer,start_tex,0,&start_rect);
        SDL_WaitEvent(&event);
        mouse_state = SDL_GetMouseState(&cord_x,&cord_y);
        if(event.type == SDL_QUIT){
            is_menu = false;
            result = 0;
            SDL_Quit();
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT){
                if (cord_x >= start_rect.x && cord_x <= start_rect.x + start_rect.w && cord_y >= start_rect.y && cord_y <= start_rect.y + start_rect.h) {
                    is_menu = false;
                    result = 1;  
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    // SDL_DestroyTexture(start_tex);
    return result;
}

int level_window(SDL_Renderer *renderer,SDL_Texture *Bgtexture, SDL_Texture *easy,SDL_Texture *medium,SDL_Texture *hard,SDL_Rect easy_rect, SDL_Rect medium_rect, SDL_Rect hard_rect){
    bool is_choice = true;
    int result;
    SDL_Event event;
    int cord_x, cord_y, mouse_state;
    while(is_choice){
        SDL_RenderCopy(renderer,Bgtexture,0,0);
        SDL_RenderCopy(renderer,easy,0,&easy_rect);
        SDL_RenderCopy(renderer,medium,0,&medium_rect);
        SDL_RenderCopy(renderer,hard,0,&hard_rect);
        SDL_WaitEvent(&event);
        mouse_state = SDL_GetMouseState(&cord_x,&cord_y);
        if(event.type == SDL_QUIT){
            is_choice = false;
            result = 0;
            SDL_Quit();
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT){
                if (cord_x >= easy_rect.x && cord_x <= easy_rect.x + easy_rect.w && cord_y >= easy_rect.y && cord_y <= easy_rect.y + easy_rect.h) {
                    is_choice = false;
                    result = 1;
                }
                if (cord_x >= medium_rect.x && cord_x <= medium_rect.x + medium_rect.w && cord_y >= medium_rect.y && cord_y <= medium_rect.y + medium_rect.h) {
                    is_choice = false;  
                    result = 2;
                }
                if (cord_x >= hard_rect.x && cord_x <= hard_rect.x + hard_rect.w && cord_y >= hard_rect.y && cord_y <= hard_rect.y + hard_rect.h) {
                    is_choice = false;  
                    result = 3;
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    // SDL_DestroyTexture(easy);
    // SDL_DestroyTexture(medium);
    // SDL_DestroyTexture(hard);
    return result;
}

void put_a_number(SDL_Renderer *renderer, SDL_Rect *obj_rect, numbers nums, char **showmap, int x, int y){
    SDL_Rect cos_rect = *obj_rect;
    cos_rect.w = 20;
    cos_rect.x = obj_rect->x +10;
    SDL_Texture *texture = nums.numbers_textures[(int)showmap[y][x]-'0'];
    SDL_RenderCopy(renderer,texture,0,&cos_rect);
}

void display_hearts(SDL_Renderer *renderer,int lives, SDL_Texture *heart_tex, SDL_Rect heart_rect){
    if(lives >= 1){
        SDL_RenderCopy(renderer,heart_tex,0,&heart_rect);
    }
    if(lives >= 2){
        heart_rect.x = heart_rect.x + 70;
        SDL_RenderCopy(renderer,heart_tex,0,&heart_rect);
    }
    if(lives == 3){
        heart_rect.x = heart_rect.x + 70;
        SDL_RenderCopy(renderer,heart_tex,0,&heart_rect);
    }
}

void display_score(SDL_Renderer *renderer,int *score, numbers white_nums, SDL_Texture *score_tex, SDL_Rect score_rect, int WIDE){
    int tmp = *score, gap = 0;
    SDL_Texture *num_tex;
    SDL_Rect num_rect = set_Rect(WIDE - 100,22,80,40);
    while (tmp != 0)
    {
        num_tex = white_nums.numbers_textures[tmp%10];
        SDL_RenderCopy(renderer,num_tex,0,&num_rect);
        score_rect.x = score_rect.x - gap * 40;
        num_rect.x = num_rect.x - 40;
        gap++;
        tmp = tmp/10;
    }
    SDL_RenderCopy(renderer,score_tex,0,&score_rect);
}

int lose_window(SDL_Renderer *renderer, SDL_Texture *restart_tex, SDL_Texture *exit_tex, SDL_Rect restart_rect,SDL_Rect exit_rect){
    bool run = true, result = false;
    SDL_Event event;
    Uint32 mouse_state;
    int cord_x, cord_y;
    while (run)
   {
       while (SDL_PollEvent(&event)) {
           if(event.type == SDL_QUIT){
               run = false;
               SDL_Quit();
           }
           mouse_state = SDL_GetMouseState(&cord_x,&cord_y);
           if (event.type == SDL_MOUSEBUTTONDOWN) {
               if(event.button.button == SDL_BUTTON_LEFT){
                   if (cord_x >= restart_rect.x && cord_x <= restart_rect.x + restart_rect.w && cord_y >= restart_rect.y && cord_y <= restart_rect.y + restart_rect.h) {
                       result = 1;
                       run = false;
                   }
                   if (cord_x >= exit_rect.x && cord_x <= exit_rect.x + exit_rect.w && cord_y >= exit_rect.y && cord_y <= exit_rect.y + exit_rect.h) {
                       result = false;
                       run  = false;
                   }
               }
           }
       }
       SDL_RenderCopy(renderer,restart_tex,0,&restart_rect);
       SDL_RenderCopy(renderer,exit_tex,0,&exit_rect);
       SDL_RenderPresent(renderer);
   }
    return result;
}

void show_bombs_sdl(SDL_Renderer *renderer, int lines, int columns, int **field, SDL_Texture *bomb_tex, SDL_Rect rectangle, int size, int space, int x){
    for (int i = lines-1; i >= 0; i--)
        {
            for (int j = 0; j < columns; j++)
            {   
                if(field[i][j] == -1){
                    SDL_SetRenderDrawColor(renderer,255,0,0,255);
                    SDL_RenderFillRect(renderer, &rectangle);
                    SDL_RenderCopy(renderer, bomb_tex, NULL, &rectangle);
                    
                
                }
                rectangle.x = rectangle.x + size + space;
            }
            rectangle.x = x;
            rectangle.y = rectangle.y - size - space;
            
        }
    SDL_RenderPresent(renderer);
}

