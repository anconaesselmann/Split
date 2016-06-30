// My_Library_IF implementation file

#include <iostream>
#include "My_Library_IF.h"
#include "al_display.h"

namespace aae {
    
    void Text_Box::set_color(COLOR color) {
        _color = color;
    }
    void Text_Box::set_font(FONT font) {
        _font = font;
    }
    Text_Box::Text_Box(double x, double y) {
        Text_Box::_initialize();
        _x = x;
        _y = y;
    }
    Text_Box::Text_Box(double x, double y, string text) {
        Text_Box::_initialize();
        _x = x;
        _y = y;
        _text = text;
        _draw_text();
    }
    void Text_Box::set(string text) {
        _text = text;
        _draw_text();
    }
    void Text_Box::_draw_text() {
        draw_text(_font, _color, _x, _y, _text);
    }
    void Text_Box::_initialize() {
        _color = COLOR_WHITE;
        _font  = FONT_TIMES;
    }
}