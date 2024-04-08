#ifndef __GRID_H__
#define __GRID_H__
struct Cell{
    enum class LifeState:unsigned char{
        DEAD=0,
        ALIVE=1
    };
    LifeState life_state_;
    unsigned char alive_neighbors_count_;
};
struct Grid{
    // row in range(0,+Inf)
    // col in range(0,+Inf)
    // else throw std::out_of_range
    static void init(long long row,long long col);
    static long long row(void)noexcept;
    static long long col(void)noexcept;
    // row in range[0,Grid::row())
    // col in range[0,Grid::col())
    // else throw std::out_of_range
    static Cell at(long long row,long long col);
    static void update(void)noexcept;
    static long long turn_count(void)noexcept;
    static long long alive_count(void)noexcept;
};
#endif//__GRID_H__
