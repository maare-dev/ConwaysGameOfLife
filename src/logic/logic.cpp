#include "logic.hpp"
#include <algorithm>
#include <vector>
#include <random>

const int D_M_SIZE = 64;
std::vector<std::vector<bool>> map(D_M_SIZE, std::vector<bool>(D_M_SIZE, false));
std::vector<std::vector<bool>> count(D_M_SIZE, std::vector<bool>(D_M_SIZE, false));

void ResizeVectorVector(int x, int y, std::vector<std::vector<bool>>& vv){
    vv.resize(y);
    for (auto& v : vv){
        v.resize(x);
    }
}
bool GetCellState(std::vector<std::vector<bool>>& vv, int x, int y){
    if (y < 0 || y >= static_cast<int>(vv.size())) return false;
    if (x < 0 || x >= static_cast<int>(vv[y].size())) return false;
    return vv[y][x];
}
void SetCellState(std::vector<std::vector<bool>>& vv, int x, int y, bool state){
    if (y < 0 || y >= static_cast<int>(vv.size())) return;
    if (x < 0 || x >= static_cast<int>(vv[y].size())) return;
    vv[y][x] = state;
}
int CountNeigbours(int x, int y){
    int result = 0;
    for (int iy = y-1; iy < y+2; iy++){
        for (int ix = x-1; ix < x+2; ix++){
            if (ix == x && iy == y) continue;
            if (GetCellState(map, ix, iy)){
                ++result;
            }
        }
    }
    return result;
}
void ClearVectorVector(std::vector<std::vector<bool>>& vv){
    for (auto& row : vv){
        std::fill(row.begin(), row.end(), false);
    }
}



void SetMapSize(int x, int y){
    ResizeVectorVector(x, y, map);
    ResizeVectorVector(x, y, count);
}
void CountStep(){
    for (size_t iy = 0; iy < map.size(); ++iy){
        for (size_t ix = 0; ix < map[iy].size(); ++ix){
            int neigbours = CountNeigbours(ix, iy);
            bool active = GetCellState(map, ix, iy);
            if (neigbours == 3){
                SetCellState(count, ix, iy, true);
            }
            else if (active && neigbours == 2){
                SetCellState(count, ix, iy, true);
            }
            else {
                SetCellState(count, ix, iy, false);
            }
        }
    }
    map = count;
    ClearVectorVector(count);
}
const std::vector<std::vector<bool>>& GetMap(){
    return map;
}
void SetCell(int x, int y, bool state){
    SetCellState(map, x, y, state);
}
bool GetCell(int x, int y){
    return GetCellState(map, x, y);
}
void ClearMap(){
    ClearVectorVector(map);
}
void RandomMap() {
    const double ALIVE_CHANCE = 0.3;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dis(ALIVE_CHANCE);

    for (size_t iy = 0; iy < map.size(); ++iy) {
        for (size_t ix = 0; ix < map[iy].size(); ++ix) {
            SetCellState(map, ix, iy, dis(gen));
        }
    }
}
