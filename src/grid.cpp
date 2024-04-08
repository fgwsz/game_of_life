#include"grid.h"
#include<vector>//std::vector
#include<random>//std::random_device std::mt19937 std::uniform_int_distribution
#include<stdexcept>//std::out_of_range
struct __CellPos{
    long long row_,col_;
};
static std::vector<std::vector<Cell>> __grid;
static long long __grid_turn_count=0;
static long long __grid_alive_count=0;
static constexpr __CellPos const __cell_dpos_array[8]={
    __CellPos{-1,-1},
    __CellPos{-1, 0},
    __CellPos{-1, 1},
    __CellPos{ 0,-1},
    __CellPos{ 0, 1},
    __CellPos{ 1,-1},
    __CellPos{ 1, 0},
    __CellPos{ 1, 1}
};
static inline Cell::LifeState __make_random_life_state(void)noexcept{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<unsigned short> distrib(0,1);
    return static_cast<Cell::LifeState>(distrib(gen));
}
long long Grid::row(void)noexcept{
    return static_cast<long long>(__grid.size());
}
long long Grid::col(void)noexcept{
    return static_cast<long long>(__grid[0].size());
}
Cell Grid::at(long long row,long long col){
    if(row<0||row>=Grid::row()||col<0||col>=Grid::col()){
        throw std::out_of_range(
            "row must be in range[0,Grid::row())"
            "and col must be in range[0,Grid::col())"
        );
    }
    return __grid[row][col];
}
static inline void __grid_update_alive_neighbors_count(void)noexcept{
    for(long long row=0;row<Grid::row();++row){
        for(long long col=0;col<Grid::col();++col){
            __grid[row][col].alive_neighbors_count_=0;
            for(__CellPos const& dpos:__cell_dpos_array){
                if(
                    __grid
                        [(row+dpos.row_+Grid::row())%Grid::row()]
                        [(col+dpos.col_+Grid::col())%Grid::col()]
                        .life_state_==Cell::LifeState::ALIVE
                ){
                    ++(__grid[row][col].alive_neighbors_count_);
                }
            }
        }
    }
}
static inline void __grid_update_alive_neighbors_count_fast(void)noexcept{
    std::vector<__CellPos> stack;
    for(long long row=0;row<Grid::row();++row){
        for(long long col=0;col<Grid::col();++col){
            __grid[row][col].alive_neighbors_count_=0;
            if(__grid[row][col].life_state_==Cell::LifeState::ALIVE){
                stack.push_back(__CellPos{row,col});
            }
        }
    }
    while(!stack.empty()){
        for(__CellPos const& dpos:__cell_dpos_array){
            ++(
                __grid
                    [(stack.back().row_+dpos.row_+Grid::row())%Grid::row()]
                    [(stack.back().col_+dpos.col_+Grid::col())%Grid::col()]
                    .alive_neighbors_count_
            );
        }
        stack.pop_back();
    }
}
void Grid::init(long long row,long long col){
    if(row<=0||col<=0){
        throw std::out_of_range(
            "row must be in range(0,+Inf)"
            "and col must be in range(0,+Inf)"
        );
    }
    __grid.reserve(row);
    __grid.resize(row);
    __grid_turn_count=0;
    __grid_alive_count=0;
    for(auto& line:__grid){
        line.reserve(col);
        line.resize(col);
        for(auto& cell:line){
            cell.life_state_=__make_random_life_state();
            if(cell.life_state_==Cell::LifeState::ALIVE){
                ++__grid_alive_count;
            }
        }
    }
    __grid_update_alive_neighbors_count_fast();
}
void Grid::update(void)noexcept{
    __grid_alive_count=0;
    for(auto& line:__grid){
        for(auto& cell:line){
            if(cell.life_state_==Cell::LifeState::ALIVE){
                if(
                    cell.alive_neighbors_count_<2
                    ||cell.alive_neighbors_count_>3
                ){
                    cell.life_state_=Cell::LifeState::DEAD;
                }else{
                    ++__grid_alive_count;
                }
            }else{
                if(cell.alive_neighbors_count_==3){
                    cell.life_state_=Cell::LifeState::ALIVE;
                    ++__grid_alive_count;
                }
            }
        }
    }
    __grid_update_alive_neighbors_count_fast();
    ++__grid_turn_count;
}
long long Grid::turn_count(void)noexcept{
    return __grid_turn_count;
}
long long Grid::alive_count(void)noexcept{
    return __grid_alive_count;
}
