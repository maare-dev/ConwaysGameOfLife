#include "shell.hpp"
#include <raylib.h>
#include <string>
#include "../themes/themes.hpp"
#include <unordered_map>
#include <functional>
#include <sstream>
#include "../utils/utils.hpp"

bool shellActive;
std::string last_command = "";
std::string command = "";
std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> commands;
std::unordered_map<std::string, std::string> aliases;
void ParseCommand(){
    int key = GetCharPressed();
    while (key > 0){
        if (key >= 32 && key <= 125) {
            command += (char)key;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_TAB)) {
        if (command.find(' ') == std::string::npos && !command.empty()){
            std::vector<std::string> matches;
            for (const auto& [commandName, _] : commands){
                if (commandName.rfind(command, 0) == 0){
                    matches.push_back(commandName);
                }
            }
            if (matches.size() == 1){
                command = matches[0];
            }
        }
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
void ExecuteCommandAlias(std::string alias){
    ExecuteCommand(aliases[alias]);
}
void RegisterCommandAlias(std::string alias, std::vector<std::string> command){
    aliases[alias] = VectorStringToString(command);
    RegisterCommand(alias, [alias](std::vector<std::string>){ExecuteCommandAlias(alias);});
}
void ExecuteShellCommand(std::vector<std::string> args){
    if (args.size() == 1){
        if (args[0] == "draw_shell"){
            DrawShell();
        }
    }
    if (args.size() == 2){
        if (args[0] == "execute_command_alias"){
            ExecuteCommandAlias(args[1]);
        }
        if (args[0] == "execute_command"){
            ExecuteCommand(args[1]);
        }
        if (args[0] == "unregister_command"){
            UnregisterCommand(args[1]);
        }
    }
    if (args.size() >= 3){
        if (args[0] == "register_command_alias"){
            std::string alias = args[1];
            args.erase(args.begin(), args.begin() + 2);
            RegisterCommandAlias(alias, args);
        }
    }
}


void RegisterShellCommands(){
    RegisterCommand("shell", ExecuteShellCommand);
}
void RegisterCommand(std::string name, std::function<void(std::vector<std::string>)> func){
    commands[name] = func;
}
void UnregisterCommand(std::string name){
    if (commands.contains(name)) commands.erase(name);
}
void ExecuteCommand(std::string commandLine){
    if (commandLine.empty()) return;

    std::stringstream ss(commandLine);
    std::string commandName;

    ss >> commandName;

    std::vector<std::string> args;
    std::string argument;
    while (ss >> argument){
        args.push_back(argument);
    }

    auto it = commands.find(commandName);
    if (it != commands.end()){
        it->second(args);
    }
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
