//
//  Cursor.h
//  MyGameTest
//
//  Created by Axel Esselmann on 12/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CURSOR_H
#define CURSOR_H
#include "coord.h"

namespace aae {
    class Cursor : public Coord {
    public:
        Cursor() : Coord() {
            _down  = false;
            _up    = false;
            _click = false;
            _updated = false;
        }
        Cursor(const Cursor& a_cursor);
        Cursor operator =(const Cursor& a_cursor);
        Coord get();
        Cursor get_Cursor();
        bool down();
        // click doesn't work, probably due to threading problems!
        bool click();
        //protected:
        void set_down();
        void set_up();
        void set_click();
        
        //protected:
        bool _down;
        bool _up;
        bool _click;
        
        bool _updated;
    };
}

#endif
