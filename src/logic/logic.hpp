#pragma once
#include <vector>

void SetMapSize(int x, int y);
void CountStep();
const std::vector<std::vector<bool>>& GetMap();
void SetCell(int x, int y, bool state);
bool GetCell(int x, int y);
void ClearMap();
void RandomMap();
