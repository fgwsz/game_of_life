#ifndef __GRID_H__
#define __GRID_H__
struct Cell{
    enum class LifeState:unsigned char{
        DEAD=0,
        ALIVE=1
    };
    LifeState life_state_;
    unsigned char alive_neighbors_count_;
    long long age_;// ALIVE Cell.age_>=0,DEAD Cell.age_=-1
};
struct Grid{
    // row in range(0,+Inf)
    // and col in range(0,+Inf)
    // else throw std::out_of_range
    static void init(long long row,long long col);
    static long long row(void)noexcept;
    static long long col(void)noexcept;
    // row in range[0,Grid::row())
    // and col in range[0,Grid::col())
    // else throw std::out_of_range
    static Cell const& at(long long row,long long col);
    static void update(void)noexcept;
    static long long turn_count(void)noexcept;
    static long long alive_count(void)noexcept;
};
#endif//__GRID_H__
