// My_Library_IF header file

#ifndef MY_LIBRARY_IF_H
#define MY_LIBRARY_IF_H
#include "coord.h"
#include "Cursor.h"

using std::string;


enum COLOR {
    COLOR_RED   = 1,
    COLOR_GREEN = 2,
    COLOR_BLUE  = 3,
    COLOR_BLACK = 4,
    COLOR_WHITE = 5,
    COLOR_YELLOW = 6,
    COLOR_GREEN_DARK = 7,
    COLOR_RED_DARK = 8
};
enum FONT {
    FONT_TIMES = 1
};
enum KEY {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_E, KEY_1, KEY_2, KEY_3, KEY_4
};

namespace aae {
    class Text_Box {
    public:
        Text_Box(double x, double y);
        Text_Box(double x, double y, string text);
        void set(string text);
        void set_color(COLOR color);
        void set_font(FONT font);
    private:
        void _initialize();
        void _draw_text();
        
        double _x;
        double _y;
        string _text;
        COLOR _color;
        FONT _font;
    };
    
}

#endif
