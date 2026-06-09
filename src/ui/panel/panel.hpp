#pragma once
#include <raylib.h>
#include "../button/button.hpp"

class Panel {
private:
    Rectangle rec;
    //Color bgColor;
    //Color borderColor;
    //Color headerTextColor;
    //Color textColor;
    const char* headerText;
    const char* text;
    bool active;
    Button& closeButton;
public:
    Panel(
        Rectangle rec,
        //Color bgColor,
        //Color borderColor,
        //Color headerTextColor,
        //Color textColor,
        const char* headerText,
        const char* text,
        bool active,
        Button& closeButton
    );
    void Draw();
    void SetActive(bool active);
    void Update();
};
