#include "menu.hpp"
#include <memory>
#include <raylib.h>
#include "../../../themes/themes.hpp"
#include "../game/game.hpp"

Menu::Menu() :
    gameButton(
        Rectangle {401, 570, 397, 28},
        "Play",
        20,
        [this](){StartGame();}
    ),
    infoButton(
        Rectangle {2, 570, 397, 28},
        "Info",
        20,
        [this]() {ShowInfoPanel();}
    ),
    closeInfoPanelButton(
        Rectangle {752, 23, 25, 25},
        "X",
        20,
        [this]() {CloseInfoPanel();}
    ),
    infoPanel(
        Rectangle {20, 20, 760, 560},
        "Info",
        "SPACE - pause/continue simulation\n"
        "LMB - toggle cell\n"
        "E - clear map\n"
        "R - clear and fill by random\n"
        "T - toggle theme\n"
        "W/S - faster/slower counting\n"
        "A/D - less/more simulations per count\n"
        "Q - quit to menu",
        false,
        closeInfoPanelButton
    )
{}
void Menu::DrawFrame(){
    if (IsKeyPressed(KEY_T)) SetCurrentThemeId(1-GetCurrentThemeId());
    Theme& theme = GetCurrentTheme();
    ClearBackground(theme.appBGColor);
    gameButton.Update();
    infoButton.Update();
    infoPanel.Update();

    int fontSize = 20;
    const char* title = "Conway's Game of Life";
    int textWeidth = MeasureText(title, fontSize);
    int posX = (800 - textWeidth) / 2;
    int posY = 15;
    DrawText(title, posX, posY, fontSize, theme.headerTextColor);
    gameButton.Draw();
    infoButton.Draw();
    infoPanel.Draw();
}
void Menu::StartGame(){
    AddScene(1, std::make_shared<Game>());
    SetCurrentSceneId(1);
}
void Menu::ShowInfoPanel(){
    infoPanel.SetActive(true);
}
void Menu::CloseInfoPanel(){
    infoPanel.SetActive(false);
}
