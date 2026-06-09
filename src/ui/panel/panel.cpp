#include "panel.hpp"
#include <raylib.h>
#include "../../themes/themes.hpp"

Panel::Panel(
    Rectangle rec,
    //Color bgColor, // app bg
    //Color borderColor, // ui lines
    //Color headerTextColor, // header text
    //Color textColor, // text color
    const char* headerText,
    const char* text,
    bool active,
    Button& closeButton
) : closeButton(closeButton){
    this->rec = rec;
    //this->bgColor = bgColor;
    //this->borderColor = borderColor;
    //this->headerTextColor = headerTextColor;
    //this->textColor = textColor;
    this->headerText = headerText;
    this->text = text;
    this->active = active;
}
void Panel::SetActive(bool active){
    this->active = active;
}
void Panel::Update() {
    if (!active) return;

    closeButton.Update();
}
void Panel::Draw(){
    Theme& ct = GetCurrentTheme();
    Color bgColor = ct.appBGColor;
    Color borderColor = ct.UILinesColor;
    Color headerTextColor = ct.headerTextColor;
    Color textColor = ct.textColor;
    if (!active) return;

    DrawRectangleRec(rec, bgColor);
    DrawRectangleLinesEx(rec, 2, borderColor);

    DrawText(headerText, rec.x + 10, rec.y + 10, 40, headerTextColor);
    DrawText(text, rec.x + 60, rec.y + 60, 20, textColor);

    closeButton.Draw();
}
