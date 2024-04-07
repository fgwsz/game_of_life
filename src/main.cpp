#include<string>//std::string std::getline std::stoll
#include<iostream>//std::cout std::cin
#include<functional>//std::function
#include"grid.h"//grid_init grid_update grid_show grid_alive_count
static bool const __iostream_init_flag=[](){
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
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
int main(void){
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
        grid_show();
        std::cout<<"Turn: "<<turn_count<<"\n";
        std::cout<<"Alive: "<<grid_alive_count()<<"\n";
        if(grid_alive_count()==0){
            std::cout<<"Game Over!\n";
            break;
        }
        std::cout<<"Command{Q/q->Quit,Others->Continue}\n";
        std::cout<<"Input Command: ";
        std::getline(std::cin,command);
        if(command=="Q"||command=="q"){
            break;
        }
        grid_update();
        ++turn_count;
    }
    return 0;
}
