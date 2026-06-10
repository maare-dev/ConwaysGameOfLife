#include <cstdlib>
#include <raylib.h>
#include "res/res.hpp"
#include "scene/scene.hpp"
#include "scene/scenes/menu/menu.hpp"
#include "themes/themes.hpp"
#include <memory>
#include "shell/shell.hpp"

void Init();
void ExitCorrectly(int code);

int main(){
    Init();
    std::shared_ptr<Scene> menuScn = std::make_shared<Menu>();
    AddScene(0, menuScn);
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
    InitWindow(800, 600, "my life sim");
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
