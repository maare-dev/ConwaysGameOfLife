#pragma once
#include <raylib.h>

struct Theme {
    Color deadCellColor;
    Color liveCellColor;
    Color gridColor;
    Color appBGColor;
    Color UILinesColor;
    Color headerTextColor;
    Color textColor;
};

void RegisterThemesCommands();

Theme& GetTheme(int id);
void SetTheme(int id, Theme theme);

Theme& GetCurrentTheme();

int GetCurrentThemeId();
void SetCurrentThemeId(int id);
