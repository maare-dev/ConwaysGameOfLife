#include "button.hpp"
#include <raylib.h>
#include "../../themes/themes.hpp"

Button::Button(
    Rectangle rec,
    const char* text,
    int fontSize,
    //Color textColor, // text color
    //Color borderColor, // ui liles
    //Color defaultColor, // app bg
    //Color enterColor, // app bg
    //Color clickColor, // dead cell
    std::function<void()> onClick
){
    this->rec = rec;
    this->text = text;
    this->fontSize = fontSize;
    //this->textColor = textColor;
    //this->borderColor = borderColor;
    //this->defaultColor = defaultColor;
    //this->enterColor = enterColor;
    //this->clickColor = clickColor;
    this->onClick = onClick;
}
bool Button::IsEntered(){
    return CheckCollisionPointRec(GetMousePosition(), rec);
}
bool Button::IsClicked(){
    return IsEntered() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
void Button::Update(){
    if (IsClicked() && onClick){
        onClick();
    }
}
void Button::Draw(){
    Theme& ct = GetCurrentTheme();
    Color textColor = ct.textColor;
    Color borderColor = ct.UILinesColor;
    Color defaultColor = ct.appBGColor;
    Color enterColor = ct.appBGColor;
    Color clickColor = ct.deadCellColor;

    Color currentColor = defaultColor;

    if (IsEntered()){
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            currentColor  = clickColor;
        }
        else {
            currentColor = enterColor;
        }
    }
    DrawRectangleRec(rec, currentColor);
    DrawRectangleLinesEx(rec, 2, borderColor);

    int textWidth = MeasureText(text, fontSize);
    int textX = rec.x + (rec.width - textWidth) / 2;
    int textY = rec.y + (rec.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, textColor);
}
