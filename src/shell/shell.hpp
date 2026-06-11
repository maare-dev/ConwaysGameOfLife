#pragma once
#include <string>
#include <vector>
#include <functional>

void RegisterShellCommands();
void RegisterCommand(std::string name, std::function<void(std::vector<std::string>)> func);
void UnregisterCommand(std::string name);
void ExecuteCommand(std::string command);
bool IsShellActive();
void UpdateShell();
void DrawShell();
