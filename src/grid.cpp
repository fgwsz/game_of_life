#include"grid.h"
extern "C"{
#include<time.h>//time
#include<stdlib.h>//srand rand
}//extern "C"
#include<vector>//std::vector
enum class __LifeState:unsigned char{
    DEAD=0,
    ALIVE=1
};
struct __Cell{
    __LifeState life_state_;
    unsigned char alive_neighbors_count_;
};
struct __CellPos{
    long long row_,col_;
};
static std::vector<__CellPos> const __cell_dpos_array={
    {-1,-1},
    {-1,0},
    {-1,1},
    {0,-1},
    {0,1},
    {1,-1},
    {1,0},
    {1,1}
};
static __LifeState __make_random_life_state(){
    static bool const random_init_flag=[](){
        srand(static_cast<unsigned>(time(nullptr)));
        return true;
    }();
    return static_cast<__LifeState>(rand()%2);
}
static std::vector<std::vector<__Cell>> __grid;
static long long __grid_alive_count=0;
static long long __grid_row(){
    return static_cast<long long>(__grid.size());
}
static long long __grid_col(){
    return static_cast<long long>(__grid.empty()?0:__grid[0].size());
}
static void __grid_update_alive_neighbors_count(){
    long long x=0,y=0;
    for(long long row=0;row<__grid_row();++row){
        for(long long col=0;col<__grid_col();++col){
            __grid[row][col].alive_neighbors_count_=0;
            for(__CellPos const& dpos:__cell_dpos_array){
                x=(row+dpos.row_+__grid_row())%__grid_row();
                y=(col+dpos.col_+__grid_col())%__grid_col();
                if(__grid[x][y].life_state_==__LifeState::ALIVE){
                    ++(__grid[row][col].alive_neighbors_count_);
                }
            }
        }
    }
}
static void __grid_update_alive_neighbors_count_fast(){
    std::vector<__CellPos> stack;
    for(long long row=0;row<__grid_row();++row){
        for(long long col=0;col<__grid_col();++col){
            __grid[row][col].alive_neighbors_count_=0;
            if(__grid[row][col].life_state_==__LifeState::ALIVE){
                stack.push_back(__CellPos{row,col});
            }
        }
    }
    long long x=0,y=0;
    while(!stack.empty()){
        for(__CellPos const& dpos:__cell_dpos_array){
            x=(stack.back().row_+dpos.row_+__grid_row())%__grid_row();
            y=(stack.back().col_+dpos.col_+__grid_col())%__grid_col();
            ++(__grid[x][y].alive_neighbors_count_);
        }
        stack.pop_back();
    }
}
void grid_init(long long row,long long col){
    __grid.reserve(row);
    __grid.resize(row);
    __grid_alive_count=0;
    for(auto& line:__grid){
        line.reserve(col);
        line.resize(col);
        for(auto& cell:line){
            cell.life_state_=__make_random_life_state();
            if(cell.life_state_==__LifeState::ALIVE){
                ++__grid_alive_count;
            }
        }
    }
    __grid_update_alive_neighbors_count_fast();
}
void grid_update(){
    unsigned char count=0;
    __grid_alive_count=0;
    for(long long row=0;row<__grid_row();++row){
        for(long long col=0;col<__grid_col();++col){
            count=__grid[row][col].alive_neighbors_count_;
            if(__grid[row][col].life_state_==__LifeState::ALIVE){
                if(count<2||count>3){
                    __grid[row][col].life_state_=__LifeState::DEAD;
                }else{
                    ++__grid_alive_count;
                }
            }else{
                if(count==3){
                    __grid[row][col].life_state_=__LifeState::ALIVE;
                    ++__grid_alive_count;
                }
            }
        }
    }
    __grid_update_alive_neighbors_count_fast();
}
std::string grid_to_string(){
    std::string ret;
    for(auto const& line:__grid){
        for(auto const& cell:line){
            if(cell.life_state_==__LifeState::ALIVE){
                ret.append("■");
            }else{
                ret.append("·");
            }
            ret.append(" ");
        }
        ret.append("\n");
    }
    return ret;
}
long long grid_alive_count(){
    return __grid_alive_count;
}
