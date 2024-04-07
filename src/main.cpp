extern "C"{
#include<time.h>//time
#include<stdlib.h>//srand rand
}//extern "C"
#include<vector>//std::vector
#include<iostream>//std::cout std::cin
#include<string>//std::string std::getline
enum class LifeState:unsigned char{
    DEAD=0,
    ALIVE=1
};
struct Cell{
    LifeState life_state_;
    unsigned char alive_neighbors_count_;
};
std::vector<std::vector<Cell>> grid;
static bool const __random_init_flag=[](){
    srand(time(nullptr));
    return true;
}();
static bool const __iostream_init_flag=[](){
    std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return true;
};
#define __make_random_life_state() \
    static_cast<LifeState>(rand()%2) \
//
static long long __grid_alive_count=0;
//
#define grid_init(/*long long*/__row__,/*long long*/__col__) do{ \
    grid.reserve(__row__); \
    grid.resize(__row__); \
    __grid_alive_count=0; \
    for(auto& line:grid){ \
        line.reserve(__col__); \
        line.resize(__col__); \
        for(auto& cell:line){ \
            cell.life_state_=__make_random_life_state(); \
            if(cell.life_state_==LifeState::ALIVE){ \
                ++__grid_alive_count; \
            } \
            cell.alive_neighbors_count_=0; \
        } \
    } \
}while(0) \
//
#define __grid_row() \
    static_cast<long long>(grid.size()) \
//
#define __grid_col() \
    static_cast<long long>(grid.empty()?0:grid[0].size())\
//
#define __grid_update_alive_neighbors_count() do{ \
    long long x=0,y=0; \
    for(long long row=0;row<__grid_row();++row){ \
        for(long long col=0;col<__grid_col();++col){ \
            grid[row][col].alive_neighbors_count_=0; \
            for(long long dx=-1;dx<=1;++dx){ \
                for(long long dy=-1;dy<=1;++dy){ \
                    x=row+dx; \
                    y=col+dy; \
                    if( \
                        !(dx==0&&dy==0) \
                        &&x>=0&&x<__grid_row() \
                        &&y>=0&&y<__grid_col() \
                        &&grid[x][y].life_state_==LifeState::ALIVE \
                    ){ \
                        ++(grid[row][col].alive_neighbors_count_); \
                    } \
                } \
            } \
        } \
    } \
}while(0) \
//
#define grid_update() do{ \
    __grid_update_alive_neighbors_count(); \
    unsigned char count=0; \
    __grid_alive_count=0; \
    for(long long row=0;row<__grid_row();++row){ \
        for(long long col=0;col<__grid_col();++col){ \
            count=grid[row][col].alive_neighbors_count_; \
            if(grid[row][col].life_state_==LifeState::ALIVE){ \
                if(count<2||count>3){ \
                    grid[row][col].life_state_=LifeState::DEAD; \
                }else{ \
                    ++__grid_alive_count; \
                } \
            }else{ \
                if(count==3){ \
                    grid[row][col].life_state_=LifeState::ALIVE; \
                    ++__grid_alive_count; \
                } \
            } \
        } \
    } \
}while(0) \
//
#define grid_alive_count() \
    (__grid_alive_count) \
//
#define grid_show() do{ \
    for(auto const& line:grid){ \
        for(auto const& cell:line){ \
            std::cout \
                <<" " \
                <<(cell.life_state_==LifeState::ALIVE \
                    ?std::string("o") \
                    :std::string("·")) \
                <<" "; \
        } \
        std::cout<<"\n"; \
    } \
}while(0) \
//
int main(void){
    std::string command="";
    long long row=0,col=0,turn_count=0;
    // read row
    while(true){
        std::cout<<"please input row (>0): ";
        std::getline(std::cin,command);
        try{
            row=std::stoll(command);
        }catch(std::exception const& error){
            std::cout<<error.what()<<"\n";
            continue;
        }
        if(row>0){
            break;
        }
    }
    // read col
    while(true){
        std::cout<<"please input col (>0): ";
        std::getline(std::cin,command);
        try{
            col=std::stoll(command);
        }catch(std::exception const& error){
            std::cout<<error.what()<<"\n";
            continue;
        }
        if(col>0){
            break;
        }
    }
    grid_init(row,col);
    while(true){
        grid_show();
        std::cout<<"turn: "<<turn_count<<"\n";
        std::cout<<"alive: "<<grid_alive_count()<<"\n";
        if(grid_alive_count()==0){
            std::cout<<"GAME OVER!\n";
            break;
        }
        std::cout<<"please press `q`->quit/others->continue ... ";
        std::getline(std::cin,command);
        if(command=="q"){
            break;
        }
        grid_update();
        ++turn_count;
    }
    return 0;
}
