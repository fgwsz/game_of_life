#ifndef __GRID_H__
#define __GRID_H__
#include<string>//std::string
void grid_init(long long row,long long col)noexcept;
void grid_update(void)noexcept;
std::string grid_to_string(void)noexcept;
long long grid_alive_count(void)noexcept;
#endif//__GRID_H__
