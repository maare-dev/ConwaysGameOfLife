#include <cstdlib>
#include <raylib.h>
#include "res/res.hpp"
#include "scene/scene.hpp"
#include "scene/scenes/menu/menu.hpp"
#include "scene/scenes/game/game.hpp"
#include "themes/themes.hpp"
#include <memory>
#include "shell/shell.hpp"

void Init();
void ExitCorrectly(int code);

int main(){
    Init();

    AddScene(0, std::make_shared<Menu>());
    AddScene(1, std::make_shared<Game>());
    SetCurrentSceneId(0);

    SetCurrentThemeId(1);

    while(!WindowShouldClose()){
        BeginDrawing();
            GetCurrentScene()->DrawFrame();
            UpdateShell();
            DrawShell();
        EndDrawing();
    }
}

void Init(){
    SetTraceLogLevel(LOG_NONE);
    InitWindow(800, 600, "Conway's Game of Life");
    SetExitKey(KEY_NULL);
    SetTargetFPS(120);
    SetTheme(0, Theme{
        WHITE,
        BLACK,
        LIGHTGRAY,
        LIGHTGRAY,
        DARKGRAY,
        BLACK,
        GRAY
    });
    SetTheme(1, Theme{
        BLACK,
        GRAY,
        DARKGRAY,
        DARKGRAY,
        WHITE,
        WHITE,
        LIGHTGRAY
    });
    InitAudioDevice();
}
void ExitCorrectly(int code){
    UnloadAllRes();
    exit(code);
}
