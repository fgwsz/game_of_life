extern "C"{
#include<stdlib.h>//system
}//extern "C"
#include<string>//std::string std::getline std::stoll
#include<iostream>//std::cout std::cin
#include<functional>//std::function
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
static void __automatic_mode(){
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
    for(;;){
        __console_clear();
        std::cout<<grid_to_string();
        std::cout<<"Turn: "<<turn_count<<"\n";
        std::cout<<"Alive: "<<grid_alive_count()<<"\n";
        if(grid_alive_count()==0){
            std::cout<<"Game Over!\n";
            return;
        }
        grid_update();
        ++turn_count;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
    }
}
static void __manual_mode(){
    long long row=__read_ll(
        "Input Row(>0): ",
        [](long long num){return num>0;}
    );
    long long col=__read_ll(
        "Input Col(>0): ",
        [](long long num){return num>0;}
    );
    grid_init(row,col);
    std::string command;
    long long turn_count=0;
    for(;;){
        std::cout<<grid_to_string();
        std::cout<<"Turn: "<<turn_count<<"\n";
        std::cout<<"Alive: "<<grid_alive_count()<<"\n";
        if(grid_alive_count()==0){
            std::cout<<"Game Over!\n";
            return;
        }
        std::cout<<"Command{Q/q->Quit,Others->Continue}\n";
        std::cout<<"Input Command: ";
        std::getline(std::cin,command);
        if(command=="Q"||command=="q"){
            return;
        }
        grid_update();
        ++turn_count;
    }
}
int main(){
    std::string command;
    std::cout<<"Command{A/a->Automatic Mode,M/m->Manual Mode}\n";
    enum class Mode:unsigned char{
        AUTOMATIC_MODE=0,
        MANUAL_MODE=1
    };
    Mode mode=Mode::AUTOMATIC_MODE;
    for(;;){
        std::cout<<"Input Command: ";
        std::getline(std::cin,command);
        if(command=="A"||command=="a"){
            mode=Mode::AUTOMATIC_MODE;
            break;
        }else if(command=="M"||command=="m"){
            mode=Mode::MANUAL_MODE;
            break;
        }
    }
    switch(mode){
        case Mode::AUTOMATIC_MODE:{__automatic_mode();break;}
        case Mode::MANUAL_MODE:{__manual_mode();break;}
    }
    return 0;
}
