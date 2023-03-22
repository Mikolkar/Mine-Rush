#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"sdl_functions.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
int main(int argc , char *argv[]){
    int columns = 0;
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr , "Failed to initialize SDL:%s\n" , SDL_GetError());
        exit(1);
    }
    //Seting display size
    int WIDE = 1080, HIGH = 720 , lines = 14;
    //Creating a window 
    SDL_Window* window = SDL_CreateWindow("Mines Rush", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,WIDE,HIGH,0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

    TTF_Init();
    // IMG_Init();
    TTF_Font* font = TTF_OpenFont("./img_&_fonts/Retro Gaming.ttf", 24);
    if(font == NULL){
        printf(":(");
    }
    SDL_Color color = {255,0,0} , black = {0,0,0}, white = {255,255,255}, blue_1 = {0,0,255}, green_2 = {0,130,0}, red_3 = {255,0,0}, dark_blue_4 = {0,0,132},
    dark_red_5 = {132,0,0}, sea_green_6 = {0,130,132}, magenta_7 = {132,0,132}, grey_8 = {117,117,117};
    numbers nums = {
        .colors={white,blue_1,green_2,red_3,dark_blue_4,dark_red_5,sea_green_6,magenta_7,grey_8},
        .numbers_Suface = {TTF_RenderText_Blended(font, "0", nums.colors[0]),TTF_RenderText_Blended(font, "1", nums.colors[1]),TTF_RenderText_Blended(font, "2", nums.colors[2]),TTF_RenderText_Blended(font, "3", nums.colors[3]),
        TTF_RenderText_Blended(font, "4", nums.colors[4]),TTF_RenderText_Blended(font, "5", nums.colors[5]),TTF_RenderText_Blended(font, "6", nums.colors[6]),
        TTF_RenderText_Blended(font, "7", nums.colors[7]),TTF_RenderText_Blended(font, "8", nums.colors[8]),TTF_RenderText_Blended(font, "9", nums.colors[0])},
        .numbers_textures = {SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[0]), SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[1]),SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[2]),
        SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[3]),SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[4]),SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[5]),
        SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[6]),SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[7]),SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[8]),
        SDL_CreateTextureFromSurface(renderer, nums.numbers_Suface[9])},
    };
    numbers white_nums;
    for (int i = 0; i < 10; i++)
    {
        char num[2] = {i+'0','\0'};
        white_nums.numbers_Suface[i] = TTF_RenderText_Blended(font,num, nums.colors[0]);
        white_nums.numbers_textures[i] = SDL_CreateTextureFromSurface(renderer,white_nums.numbers_Suface[i]);
        SDL_FreeSurface(nums.numbers_Suface[i]);
        SDL_FreeSurface(white_nums.numbers_Suface[i]);
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, "SCORE: ", white), *title = TTF_RenderText_Blended(font, "MINES RUSH ", white),  *title_cp = TTF_RenderText_Blended(font, "MINES RUSH ", black);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface) , *Bgtexture = Create_texture(renderer,"./img_&_fonts/Background.png");
    SDL_Texture* title_tex = SDL_CreateTextureFromSurface(renderer, title), *title_cp_tex = SDL_CreateTextureFromSurface(renderer, title_cp), *flag_tex = Create_texture(renderer,"./img_&_fonts/flag_img.png");
    SDL_Texture* start_tex  = Create_texture(renderer,"./img_&_fonts/start_btn.png"), *easy_tex = Create_texture(renderer,"./img_&_fonts/easy_btn.png"), *bomb_tex = Create_texture(renderer,"./img_&_fonts/bomb_img.png");
    SDL_Texture *medium_tex = Create_texture(renderer,"./img_&_fonts/medium_btn.png"), *hard_tex = Create_texture(renderer, "./img_&_fonts/hard_btn.png"), *heart_tex = Create_texture(renderer,"./img_&_fonts/heart_img.png");
    SDL_Texture *restart_tex = Create_texture(renderer,"./img_&_fonts/restart_btn.png"), *exit_tex = Create_texture(renderer,"./img_&_fonts/exit_btn.png");
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(title);
    SDL_Event event;

    bool is_running = true, first_click = false, is_menu = true,new_map = false, key_down = true, game_status = true, restart = false;
    int cord_x = 0, cord_y = 0,x,y,size,space, result, result_m,size_h = lines, lives;
    int **field, **hidden, wynik = 0, *score = &wynik;
    char **showmap;
    SDL_Rect rectangle,textRect,back, title_rect = set_Rect((WIDE - 642)/2,170,200,660), restart_rect = set_Rect((WIDE - 351)/2,200,126,351), exit_rect = set_Rect((WIDE - 207)/2,340,126,207);
    SDL_Rect start_rect = set_Rect((WIDE - 279)/2,(HIGH)/2,126,279), easy_rect = set_Rect((WIDE - 526)/2, 220,126,234), heart_rect = set_Rect(20,20,80,80);
    SDL_Rect medium_rect = set_Rect((WIDE - 334)/2, 380,126,334) , hard_rect = set_Rect((WIDE)/2+11, 220,126,252);
    Uint32 mouse_state;
    SDL_UpdateWindowSurface(window);
    while (is_running)
    {
        if(is_menu){
            if(restart == true){
                free_showmap(showmap, lines);
                free_field(field, lines);
                free_field(hidden, lines);    
            }
            result_m = menu(renderer,Bgtexture,start_tex,title_tex,title_cp_tex,start_rect,title_rect);
            if(result_m == 0){
                is_running  = false;
                SDL_Quit();
                return 0;
            }
            result = level_window(renderer,Bgtexture,easy_tex,medium_tex,hard_tex,easy_rect,medium_rect,hard_rect);
            if(result == 1) columns = 10;
            else if(result == 2) columns = 14;
            else if(result == 3) columns = 18;
            else{
                is_running = false;
            }
            is_running = true, first_click = false, is_menu = true,new_map = false, key_down = true, game_status = true, restart = false;
            lives = 3;
            wynik = 0;
            size = 40, space = 2;
            x = WIDE/2 - (columns * (size + space) - space)/2 , y = HIGH - 65;
            int back_high = y - (size + space)*lines + size + space;
            showmap = create_showmap(lines,columns);
            field = create_field(lines,columns);
            hidden = create_field(lines,columns);
            textRect = set_Rect(WIDE - 300,10,100,200);
            back = set_Rect(x,back_high,(size + space)*lines - space, (size + space) * columns - space);
            rectangle = set_Rect(x,y,size,size);
            fill_with_hash(lines,columns,showmap);
            is_menu = false;
            restart = false;
        }
        SDL_RenderCopy(renderer,Bgtexture,0,0);
        SDL_SetRenderDrawColor(renderer ,0,0,0,255);
        SDL_RenderFillRect(renderer, &back);
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT){
           is_running = false;
        }
        
        for (int i = lines-1; i >= 0; i--)
        {
            for (int j = 0; j < columns; j++)
            {   
                mouse_state = SDL_GetMouseState(&cord_x, &cord_y);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    if(event.button.button == SDL_BUTTON_LEFT){
                        if (cord_x >= rectangle.x && cord_x <= rectangle.x + rectangle.w && cord_y >= rectangle.y && cord_y <= rectangle.y + rectangle.h) {
                            showmap[i][j] = '.';
                            if(first_click == false){
                                set_bombs_point(lines,columns,field,j,i,true);
                                first_click = true;
                                new_map = true;
                            }
                            showmap = show_cells_point(lines,columns,field,showmap,j,i);
                            if(field[i][j] == -1 && showmap[i][j] == '.'){
                            lives--;
                        }
                        }
                        
                    }
                    else if(event.button.button == SDL_BUTTON_RIGHT){
                        if (cord_x >= rectangle.x && cord_x <= rectangle.x + rectangle.w && cord_y >= rectangle.y && cord_y <= rectangle.y + rectangle.h) {                        
                            if(showmap[i][j] == '#' || showmap[i][j] == '.' && field[i][j] != -1) showmap[i][j] = 'F';
                            else if(showmap[i][j] == 'F'){ 
                                showmap[i][j] = '#';
                                
                            }
                        }
                    }
                }
                else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
                    if(key_down){
                        game_status = check_last_line_point(lines,columns,field,showmap,score);
                        remove_last_line_point(lines,columns,field,size_h,hidden,showmap);
                        size_h--;
                        if(size_h == 0){
                            new_map = true;
                            size_h = lines;
                        }
                        if(game_status == false){
                            lives--;
                        }
                        key_down = false;
                    }
                }
                else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
                    is_menu = true;
                    restart = true;
                }
                else if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE){
                    key_down = true;
                }
                if(showmap[i][j] == '#' || showmap[i][j] == 'F'){
                    SDL_SetRenderDrawColor(renderer,179,70,57,255);
                    SDL_RenderFillRect(renderer, &rectangle);
                    if(showmap[i][j] == 'F'){
                        SDL_RenderCopy(renderer, flag_tex, NULL, &rectangle);
                    }
                }
                else{
                    SDL_SetRenderDrawColor(renderer,210,180,140,255);
                    SDL_RenderFillRect(renderer, &rectangle);
                    if((int)(showmap[i][j]-'0') >= 1 && (int)(showmap[i][j]-'0') <= 8){
                        put_a_number(renderer,&rectangle,nums,showmap,j,i);
                    }
                    else if(showmap[i][j] == '.' && field[i][j] == -1){
                        SDL_RenderCopy(renderer, bomb_tex, NULL, &rectangle);
                    }
                }
                rectangle.x = rectangle.x + size + space;
            }
            rectangle.x = x;
            rectangle.y = rectangle.y - size - space;
            
        }
        rectangle.y = y;
    
        if(new_map == true){
            set_bombs_point(lines,columns,hidden,0,0,false);
            new_map = false;
        }
        display_hearts(renderer,lives,heart_tex,heart_rect);
        display_score(renderer,score,white_nums,textTexture,textRect,WIDE);
        if(lives == 0){
            show_bombs_sdl(renderer,lines,columns,field,bomb_tex,rectangle,size,space,x);
            SDL_Delay(1000);
            is_menu = lose_window(renderer,restart_tex,exit_tex,restart_rect,exit_rect);
            if(is_menu == false){ 
                is_running = false;
            }
            else{
                restart = true;
            }
        }
        SDL_RenderPresent(renderer);
    }
    //To free memory 
    SDL_DestroyTexture(textTexture); 
    SDL_DestroyTexture(title_cp_tex),
    SDL_DestroyTexture(title_tex);
    SDL_DestroyTexture(flag_tex);
    SDL_DestroyTexture(bomb_tex);
    SDL_DestroyTexture(Bgtexture);
    SDL_DestroyTexture(restart_tex);
    SDL_DestroyTexture(exit_tex);
    SDL_DestroyTexture(start_tex);
    SDL_DestroyTexture(restart_tex);
    SDL_DestroyTexture(heart_tex);
    SDL_DestroyTexture(easy_tex);
    SDL_DestroyTexture(medium_tex);
    SDL_DestroyTexture(hard_tex);
    for (int i = 0; i < 10; i++)
    {
        SDL_DestroyTexture(nums.numbers_textures[i]);
        SDL_DestroyTexture(white_nums.numbers_textures[i]);
    }
    free_showmap(showmap, lines);
    free_field(field, lines);
    free_field(hidden, lines);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}