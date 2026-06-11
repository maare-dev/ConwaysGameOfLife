#include "themes.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include "../shell/shell.hpp"

std::unordered_map<int, Theme> themes;
int currentThemeId = 0;
void ExecuteThemesCommand(std::vector<std::string> args){
    if (args.size() == 2){
        if (args[0] == "set_current_theme_id"){
            try{
                SetCurrentThemeId(std::stoi(args[1]));
            }catch(...){}
        }
    }
}

void RegisterThemesCommands(){
    RegisterCommand("themes", ExecuteThemesCommand);
}
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
