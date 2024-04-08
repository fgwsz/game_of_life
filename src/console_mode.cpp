#include"console_mode.h"
#include<cstdlib>//std::system
#include<string>//std::string std::getline std::stoll std::to_string
#include<iostream>//std::cout std::cin
#include<functional>//std::function
#include<chrono>//std::chrono
#include<thread>//std::this_thread
#include"grid.h"//Cell Grid
static bool const __iostream_init_flag=[](void)noexcept->bool{
    std::cout.tie(nullptr);
    return true;
}();
static inline long long __read_ll(
    std::string const& prompt,
    std::function<bool(long long)> const& pred
)noexcept{
    std::string input;
    long long ret=0;
    for(;;){
        std::cout<<prompt;
        std::getline(std::cin,input);
        try{
            ret=std::stoll(input);
        }catch(std::exception const& exception){
            std::cout<<exception.what()<<"\n";
            continue;
        }
        if(pred(ret)){
            break;
        }
    }
    return ret;
}
static inline void __console_clear(void)noexcept{
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}
static inline std::string __grid_to_string(void)noexcept{
    std::string ret;
    for(long long row=0;row<Grid::row();++row){
        for(long long col=0;col<Grid::col();++col){
            switch(Grid::at(row,col).life_state_){
                case Cell::LifeState::ALIVE:{
                    ret.append("■");
                    break;
                }
                case Cell::LifeState::DEAD:{
                    ret.append("·");
                    break;
                }
            }
            ret.append(" ");
        }
        ret.append("\n");
    }
    return ret;
}
int console_mode(void)noexcept{
    long long row=__read_ll(
        "Input Row(>0): ",
        [](long long num)->bool{return num>0;}
    );
    long long col=__read_ll(
        "Input Col(>0): ",
        [](long long num)->bool{return num>0;}
    );
    Grid::init(row,col);
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::milliseconds duration;
    std::chrono::milliseconds const once_total_time(500);
    for(;;){
        start_time=std::chrono::high_resolution_clock::now();
        __console_clear();
        std::cout<<(
            __grid_to_string()
            +"Turn:"
            +std::to_string(Grid::turn_count())
            +"\nAlive:"
            +std::to_string(Grid::alive_count())
            +"\n"
        );
        if(Grid::alive_count()==0){
            std::cout<<"Game Over!\n";
            break;
        }
        Grid::update();
        duration=std::chrono::duration_cast<decltype(duration)>(
            std::chrono::high_resolution_clock::now()-start_time
        );
        if(duration<once_total_time){
            std::this_thread::sleep_for(once_total_time-duration);
        }
    }
    return 0;
}
