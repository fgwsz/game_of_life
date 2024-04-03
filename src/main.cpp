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
LifeState make_random_life_state();
struct Cell{
    LifeState life_state_;
    unsigned char alive_neighbors_count_;
};
std::vector<std::vector<Cell>> grid;
void grid_init(long long row,long long col);
long long grid_row();
long long grid_col();
void grid_update();
void grid_show();
int main(){
    std::string command="";
    long long row=0,col=0,turn_count=0;
    while(true){
        std::cout<<"please input row: ";
        std::getline(std::cin,command);
        try{
            row=std::stoll(command);
        }catch(std::invalid_argument const& error_1){
            std::cout<<error_1.what()<<"\n";
            continue;
        }catch(std::out_of_range const& error_2){
            std::cout<<error_2.what()<<"\n";
            continue;
        }
        if(row>0){
            break;
        }
    }
    while(true){
        std::cout<<"please input col: ";
        std::getline(std::cin,command);
        try{
            col=std::stoull(command);
        }catch(std::invalid_argument const& error_1){
            std::cout<<error_1.what()<<"\n";
            continue;
        }catch(std::out_of_range const& error_2){
            std::cout<<error_2.what()<<"\n";
            continue;
        }
        if(col>0){
            break;
        }
    }
    grid_init(row,col);
    while(true){
        grid_show();
        std::cout<<"current turn: "<<turn_count<<"\n";
        std::cout<<"please press a key(not q) to continue or press q to quit ... ";
        std::getline(std::cin,command);
        if(command=="q"){
            break;
        }
        grid_update();
        ++turn_count;
    }
    return 0;
}
LifeState make_random_life_state(){
    static bool random_init=false;
    if(!random_init){
        srand(time(nullptr));
        random_init=true;
    }
    return static_cast<LifeState>(rand()%2);
}
void grid_init(long long row,long long col){
    grid.reserve(row);
    grid.resize(row);
    for(auto& line:grid){
        line.reserve(col);
        line.resize(col);
        for(auto& cell:line){
            cell.life_state_=make_random_life_state();
            cell.alive_neighbors_count_=0;
        }
    }
}
long long grid_row(){
    return grid.size();
}
long long grid_col(){
    if(grid.empty()){
        return 0;
    }
    return grid[0].size();
}
void grid_update_alive_neighbors_count(){
    long long x=0,y=0;
    for(long long row=0;row<grid_row();++row){
        for(long long col=0;col<grid_col();++col){
            grid[row][col].alive_neighbors_count_=0;
            for(long long dx=-1;dx<=1;++dx){
                for(long long dy=-1;dy<=1;++dy){
                    x=row+dx;
                    y=col+dy;
                    if(x<0||y<0||x>=grid_row()||y>=grid_col()||(dx==0&&dy==0)){
                        continue;
                    }
                    if(grid[x][y].life_state_==LifeState::ALIVE){
                        ++(grid[row][col].alive_neighbors_count_);
                    }
                }
            }
        }
    }
}
void grid_update(){
    grid_update_alive_neighbors_count();
    unsigned char count=0;
    for(long long row=0;row<grid_row();++row){
        for(long long col=0;col<grid_col();++col){
            count=grid[row][col].alive_neighbors_count_;
            if(grid[row][col].life_state_==LifeState::ALIVE){
                if(count<2||count>3){
                    grid[row][col].life_state_=LifeState::DEAD;
                }
            }else{
                if(count==3){
                    grid[row][col].life_state_=LifeState::ALIVE;
                }
            }
        }
    }
}
void grid_show(){
    for(auto const& line:grid){
        for(auto const& cell:line){
            std::cout
                <<" "
                <<(cell.life_state_==LifeState::ALIVE
                    ?std::string("o")
                    :std::string(" "))
                <<" ";
        }
        std::cout<<"\n";
    }
}
