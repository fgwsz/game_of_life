#include"sdl_mode.h"
#include"SDL.h"
#include<stdio.h>
int sdl_mode(int argc,char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if(window==NULL){
        printf("SDL_CreateWindow Error:%s\n",SDL_GetError());
        return 1;
    }
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
