#pragma once
#include "../../scene.hpp"
#include "../../../ui/button/button.hpp"
#include "../../../ui/panel/panel.hpp"

class Menu : public Scene {
private:
    Button gameButton;
    Button infoButton;
    Button closeInfoPanelButton;
    Panel infoPanel;
    void StartGame();
    void ShowInfoPanel();
    void CloseInfoPanel();
    void ExecuteMenuCommand(std::vector<std::string>);
public:
    Menu();
    ~Menu();
    void DrawFrame() override;
};
