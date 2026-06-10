#include "shell.hpp"
#include <raylib.h>
#include <string>
#include "../logic/logic.hpp"
#include "../themes/themes.hpp"
#include "../scene/scene.hpp"

bool shellActive;
std::string last_command = "";
std::string command = "";
void ParseCommand(){
    int key = GetCharPressed();
    while (key > 0){
        if (key >= 32 && key <= 125) {
            command += (char)key;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !command.empty()){
        command.pop_back();
    }
    if (IsKeyPressed(KEY_UP)){
        command = last_command;
    }
    if (IsKeyPressed(KEY_ENTER)){
        shellActive = false;
        last_command = command;
        ExecuteCommand(command);
        command.clear();
    }
    if (IsKeyPressed(KEY_ESCAPE)){
        shellActive = false;
        command.clear();
    }
}


void ExecuteCommand(std::string& command){
    if (command == "map clear"){
        ClearMap();
    }
    else if (command == "map simulate"){
        CountStep();
    }
    else if (command == "map randomize"){
        RandomMap();
    }
    else if (command == "scene menu"){
        SetCurrentSceneId(0);
    }
    else if (command == "scene game"){
        SetCurrentSceneId(1);
    }
    // etc
}
bool IsShellActive(){
    return shellActive;
}
void UpdateShell(){
    if (shellActive) {
        ParseCommand();
        return;
    }
    int key = GetCharPressed();
    while (key > 0){
        if (
            IsKeyPressed(KEY_ENTER) ||
            key == ':' ||
            key == '>' ||
            key == '/'
        ){
            command.clear();
            shellActive = true;
            ParseCommand();
            break;
        }
        key = GetCharPressed();
    }
}
void DrawShell(){
    if (!shellActive) return;
    Theme& ct = GetCurrentTheme();
    Rectangle rec = {10, 10, 780, 25};
    DrawRectangleRec(rec, ct.appBGColor);
    DrawRectangleLinesEx(rec, 2, ct.UILinesColor);
    std::string drawText = "> " + command + "|";
    DrawText(drawText.c_str(), 12, 12, 20, ct.textColor);
}
