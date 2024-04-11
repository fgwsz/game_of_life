#include"sdl_mode.h"
#include"SDL.h"
#include"grid.h"//Cell Grid
static constexpr char const __window_title[]="Game Of Life";
static constexpr double const __screen_width_scale=0.75;
static constexpr double const __screen_height_scale=0.75;
struct __ColorRGB{
    long long r_,g_,b_;
};
static constexpr __ColorRGB const __cell_color_dead{0,0,0};
static constexpr __ColorRGB const __cell_color_alive_begin{0,255,0};
static constexpr __ColorRGB const __cell_color_alive_end{255,0,255};
static inline Uint32 __cell_to_color(Cell const& cell);
int sdl_mode(int argc,char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        SDL_Log("SDL_Init failed:%s",SDL_GetError());
        return -1;
    }
    SDL_DisplayMode display_mode;
    if(SDL_GetDesktopDisplayMode(0,&display_mode)<0){
        SDL_Log("SDL_GetDesktopDisplayMode failed:%s",SDL_GetError());
        return -1;
    }
    int window_width=static_cast<int>(
        static_cast<double>(display_mode.w)
        *__screen_width_scale
    );
    int window_height=static_cast<int>(
        static_cast<double>(display_mode.h)
        *__screen_height_scale
    );
    SDL_Window* window=SDL_CreateWindow(
        __window_title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_SHOWN
    );
    if(NULL==window){
        SDL_Log("SDL_CreateWindow failed:%s",SDL_GetError());
        return -1;
    }
    SDL_Surface* icon=SDL_LoadBMP("res/icon.bmp");
    if(NULL==icon){
        SDL_Log("SDL_LoadBMP failed:%s",SDL_GetError());
        return -1;
    }
    SDL_SetWindowIcon(window,icon);
    SDL_Surface* surface=SDL_GetWindowSurface(window);
    if(NULL==surface){
        SDL_Log("SDL_GetWindowSurface failed:%s",SDL_GetError());
        return -1;
    }
    Grid::init(window_height,window_width);
    SDL_Rect rect={0,0,1,1};
    SDL_Event event;
    for(;;){
        for(long long row=0;row<Grid::row();++row){
            for(long long col=0;col<Grid::col();++col){
                rect.y=static_cast<int>(row);
                rect.x=static_cast<int>(col);
                SDL_FillRect(surface,&rect,__cell_to_color(Grid::at(row,col)));
            }
        }
        SDL_UpdateWindowSurface(window);
        Grid::update();
        SDL_Log("Row:%d,Col:%d,Turn:%d,Alive:%d(%.2f%%)",
            Grid::row(),
            Grid::col(),
            Grid::turn_count(),
            Grid::alive_count(),
            static_cast<double>(Grid::alive_count())
            /static_cast<double>(Grid::row()*Grid::col())
            *double(100)
        );
        if(!SDL_PollEvent(&event)){
            continue;
        }
        if(event.type==SDL_QUIT){
            break;
        }
    }
    SDL_FreeSurface(surface);
    SDL_FreeSurface(icon);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
static inline __ColorRGB __get_sub_color_rgb(
    __ColorRGB const& from,
    __ColorRGB const& to,
    long long steps,
    long long index
){
    return {
        static_cast<long long>(from.r_+double(index)*((to.r_-from.r_)/double(steps))),
        static_cast<long long>(from.g_+double(index)*((to.g_-from.g_)/double(steps))),
        static_cast<long long>(from.b_+double(index)*((to.b_-from.b_)/double(steps)))
    };
}
static inline Uint32 __color_rgb_to_uint32(__ColorRGB const& color){
    return
        (static_cast<Uint32>(color.r_)<<16)|
        (static_cast<Uint32>(color.g_)<<8)|
        (static_cast<Uint32>(color.b_));
}
static constexpr long long const __sub_color_rgb_index_map[]={
    ((long long)1<<(long long) 1)-(long long)1,
    ((long long)1<<(long long) 2)-(long long)1,
    ((long long)1<<(long long) 3)-(long long)1,
    ((long long)1<<(long long) 4)-(long long)1,
    ((long long)1<<(long long) 5)-(long long)1,
    ((long long)1<<(long long) 6)-(long long)1,
    ((long long)1<<(long long) 7)-(long long)1,
    ((long long)1<<(long long) 8)-(long long)1,
    ((long long)1<<(long long) 9)-(long long)1,
    ((long long)1<<(long long)10)-(long long)1
};
static constexpr long long const __sub_color_rgb_max_steps=
    sizeof(__sub_color_rgb_index_map)/sizeof(__sub_color_rgb_index_map[0]);

static inline long long __get_sub_color_rgb_index(long long number){
    for(long long index=0;auto const& ele:__sub_color_rgb_index_map){
        if(number<ele){
            return index;
        }
        ++index;
    }
    return __sub_color_rgb_max_steps;
}
static inline Uint32 __cell_to_color(Cell const& cell){
    __ColorRGB ret;
    if(cell.age_<0){
        ret=__cell_color_dead;
    }else{
        auto index=__get_sub_color_rgb_index(cell.age_);
        if(index==__sub_color_rgb_max_steps){
            ret=__cell_color_alive_end;
        }else{
            ret=__get_sub_color_rgb(
                __cell_color_alive_begin,
                __cell_color_alive_end,
                __sub_color_rgb_max_steps,
                index
            );
        }
    }
    return __color_rgb_to_uint32(ret);
}
