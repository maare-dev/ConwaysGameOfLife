#pragma once
#include "../../scene.hpp"
#include "../../../ui/button/button.hpp"
#include "../../../ui/panel/panel.hpp"

class Game : public Scene {
private:
    Button closePausePanelButton;
    Panel pausePanel;
    float secPerSim;
    float sec;
    bool isRunning;
    int cellSize;
    int simsPerCount;
    void ClosePausePanel();
    void CheckForHotkeys();
    void ExecuteGameCommand(std::vector<std::string>);
public:
    Game();
    ~Game();
    void DrawFrame() override;
};
