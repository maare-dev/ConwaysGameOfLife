#pragma once
#include <raylib.h>
#include <functional>

class Button {
private:
    Rectangle rec;
    const char* text;
    int fontSize;
    //Color textColor;
    //Color borderColor;
    //Color defaultColor;
    //Color enterColor;
    //Color clickColor;
    std::function<void()> onClick;

public:
    Button(
        Rectangle rec,
        const char* text,
        int fontSize,
        //Color textColor,
        //Color borderColor,
        //Color defaultColor,
        //Color enterColor,
        //Color clickColor,
        std::function<void()> onClick
    );
    void Draw();
    void Update();
    bool IsClicked();
    bool IsEntered();
};
