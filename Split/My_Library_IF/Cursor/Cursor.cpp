//

#include <iostream>
#include "coord.h"
#include "Cursor.h"
#include "al_display.h" // remove once clicking is fixed!!!!!!!!!!

namespace aae {
    Cursor::Cursor(const Cursor& a_cursor) {
        _up = a_cursor._up;
        _down = a_cursor._down;
        _click = a_cursor._click;
        _x = a_cursor._x;
        _y = a_cursor._y;
        _updated = a_cursor._updated;
    }
    Cursor Cursor::operator =(const Cursor& a_cursor) {
        if (this != &a_cursor) {
            _up = a_cursor._up;
            _down = a_cursor._down;
            _click = a_cursor._click;
            _x = a_cursor._x;
            _y = a_cursor._y;
            _updated = a_cursor._updated;
        }
        return *this;
    }
    Coord Cursor::get() {
        return Coord(X(), Y());
    }
    Cursor Cursor::get_Cursor() {
        Cursor returnCursor;
        returnCursor._up = _up;
        returnCursor._down = _down;
        returnCursor._click = _click;
        returnCursor._x = _x;
        returnCursor._y = _y;
        returnCursor._updated = _updated;
        return returnCursor;
        // return *this;
    }
    bool Cursor::down() {
        return _down;
    }
    // click doesn't work, probably due to threading problems!
    bool Cursor::click() {
        if (_down) {
            if (_click) {
                if (_updated) {
                    std::cout << "Click called, down: " << _down << ", up: " << _up << ", click: " << _click << "\n";
                    _click = false;
                    _updated = false;
                    al_rest(.2);
                    return true;
                }
                
            }
        }
        return false;
    }
    //protected:
    void Cursor::set_down() {
        _down  = true;
        if (_up == true) {
            set_click();
            std::cout << "*********setting click\n";
        }
        _up = false;
        std::cout << "setting down\n";
    }
    void Cursor::set_up() {
        _down = false;
        _up   = true;
        std::cout << "Setting up\n";
        _click = false;
    }
    void Cursor::set_click() {
        _click = true;
        _up = false;
        std::cout << "**********************setting click!!!!!!!!!!!!!!!\n";
    }

}