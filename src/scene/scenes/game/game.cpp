#include "game.hpp"
#include <climits>
#include <cstddef>
#include <curses.h>
#include <raylib.h>
#include "../../../logic/logic.hpp"
#include <string>
#include <vector>
#include "../../../themes/themes.hpp"
#include "../../../shell/shell.hpp"
#include "../../../utils/utils.hpp"

Game::Game() :
    closePausePanelButton(
        Rectangle {23, 143, 754, 434},
        "OK",
        60,
        [this]() {ClosePausePanel();}
    ),
    pausePanel(
        Rectangle {20, 20, 760, 560},
        "Pause",
        "simulation paused\npress SPACE again to continue simulation",
        false,
        closePausePanelButton
    )
{
    secPerSim = 1;
    sec = 0;
    isRunning = true;
    cellSize = 10;
    simsPerCount = 1;
    SetMapSize(80, 60);
    RandomMap();
    RegisterCommand("game", [this](std::vector<std::string> args){ExecuteGameCommand(args);});
}
void Game::ClosePausePanel(){
    pausePanel.SetActive(false);
    Vector2 pos = GetMousePosition();
    pos.x /= cellSize;
    pos.y /= cellSize;
    SetCell(pos.x, pos.y, !GetCell(pos.x, pos.y));
}
void Game::CheckForHotkeys(){
    if (IsShellActive()) return;
    if (IsKeyPressed(KEY_SPACE)) isRunning = !isRunning;
    if (IsKeyPressed(KEY_E)) ClearMap();
    if (IsKeyPressed(KEY_R)) RandomMap();
    if (IsKeyPressed(KEY_T)) SetCurrentThemeId(1-GetCurrentThemeId());
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 pos = GetMousePosition();
        pos.x /= cellSize;
        pos.y /= cellSize;
        SetCell(pos.x, pos.y, !GetCell(pos.x, pos.y));
    }
    if (IsKeyPressed(KEY_W)) secPerSim /= 2;
    if (IsKeyPressed(KEY_S)) secPerSim *= 2;
    if (IsKeyPressed(KEY_A) && simsPerCount > 1) --simsPerCount;
    if (IsKeyPressed(KEY_D)) ++simsPerCount;
    if (IsKeyPressed(KEY_Q)) SetCurrentSceneId(0);
}
void Game::ExecuteGameCommand(std::vector<std::string> args){
    if (args.size() == 1){
        if (args[0] == "emulate_space") isRunning = !isRunning;
        if (args[0] == "emulate_e") ClearMap();
        if (args[0] == "emulate_r") RandomMap();
        if (args[0] == "emulate_t") SetCurrentThemeId(1-GetCurrentThemeId());
        if (args[0] == "emulate_w") secPerSim /= 2;
        if (args[0] == "emulate_s") secPerSim *= 2;
        if (args[0] == "emulate_a" && simsPerCount > 1) --simsPerCount;
        if (args[0] == "emulate_d") ++simsPerCount;
        if (args[0] == "emulate_q") SetCurrentSceneId(0);
    }
    if (args.size() == 2){
        if (args[0] == "is_running"){
            isRunning = StringToBool(args[1]);
        }
        else if (args[0] == "sec_per_sim"){
            try{
                int sec = std::stoi(args[1]);
                if (sec > 0.01){
                    secPerSim = sec;
                }
            }catch(...){}
        }
        else if (args[0] == "sims_per_count"){
            try{
                int sims = std::stoi(args[1]);
                if (sims > 0){
                    simsPerCount = sims;
                }
            }catch(...){}
        }
    }
}
void Game::DrawFrame(){
    static bool needToShowPanel = true;
    Theme& theme = GetCurrentTheme();
    ClearBackground(theme.appBGColor);
    CheckForHotkeys();
    if (isRunning){
        needToShowPanel = true;
        pausePanel.SetActive(false);
        sec += GetFrameTime();
        while (sec >= secPerSim){
            sec -= secPerSim;
            for (int i = 0; i < simsPerCount; i++){
                CountStep();
            }
        }
    }
    const std::vector<std::vector<bool>>& map = GetMap();
    for (size_t iy = 0; iy < map.size(); ++iy){
        for (size_t ix = 0; ix < map[iy].size(); ++ix){
            Color color;
            if (map[iy][ix]){
                color = theme.liveCellColor;
            }
            else{
                color = theme.deadCellColor;
            }
            DrawRectangle(ix*cellSize, iy*cellSize, cellSize, cellSize, color);
            DrawLine(ix*cellSize, iy*cellSize, ix*cellSize + cellSize, iy*cellSize, theme.gridColor);
            DrawLine(ix*cellSize, iy*cellSize, ix*cellSize, iy*cellSize + cellSize, theme.gridColor);
        }
    }

    if (!isRunning){
        if (needToShowPanel){
            pausePanel.SetActive(true);
            needToShowPanel = false;
        }
    }

    pausePanel.Update();
    pausePanel.Draw();
}
Game::~Game(){
    UnregisterCommand("game");
}
