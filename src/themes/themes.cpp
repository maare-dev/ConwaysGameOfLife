#include "themes.hpp"
#include <unordered_map>

std::unordered_map<int, Theme> themes;
int currentThemeId = 0;

Theme& GetTheme(int id){
    return themes[id];
}
void SetTheme(int id, Theme theme){
    themes[id] = theme;
}
Theme& GetCurrentTheme(){
    return themes[currentThemeId];
}
int GetCurrentThemeId(){
    return currentThemeId;
}
void SetCurrentThemeId(int id){
    currentThemeId = id;
}
