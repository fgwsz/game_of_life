extern "C"{
#include<stdlib.h>//system
}//extern "C"
#include<string>//std::string std::getline std::stoll
#include<iostream>//std::cout std::cin
#include<functional>//std::function
#include<chrono>//std::chrono
#include<thread>//std::this_thread
#include"grid.h"//grid_init grid_update grid_show grid_alive_count
static bool const __iostream_init_flag=[](){
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    //std::cout<<std::unitbuf;
    return true;
}();
static long long __read_ll(
    std::string const& prompt,
    std::function<bool(long long)> const& pred
){
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
static void __console_clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
int main(){
    long long row=__read_ll(
        "Input Row(>0): ",
        [](long long num){return num>0;}
    );
    long long col=__read_ll(
        "Input Col(>0): ",
        [](long long num){return num>0;}
    );
    grid_init(row,col);
    long long turn_count=0;
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::milliseconds duration;
    std::chrono::milliseconds const once_total_time(500);
    for(;;){
        start_time=std::chrono::high_resolution_clock::now();
        __console_clear();
        std::cout<<grid_to_string();
        std::cout<<"Turn: "<<turn_count<<"\n";
        std::cout<<"Alive: "<<grid_alive_count()<<"\n";
        if(grid_alive_count()==0){
            std::cout<<"Game Over!\n";
            break;
        }
        grid_update();
        ++turn_count;
        duration=std::chrono::duration_cast<decltype(duration)>(
            std::chrono::high_resolution_clock::now()-start_time
        );
        if(duration<once_total_time){
            std::this_thread::sleep_for(once_total_time-duration);
        }
    }
    return 0;
}
