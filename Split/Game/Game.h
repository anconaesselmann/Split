//
//  Game.h
//  MyGameTest
//
//  Created by Axel Esselmann on 12/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAME_H
#define GAME_H
#include "Cursor.h"
#include "grid.h"
#include "Pixel_Grid.h"
#include "Game_Control.h"
#include "Game_Board.h"
#include "Object_Space.h"
//#include "My_Library_IF.h" // right now for access to keyboard, remove later

namespace aae {
    class Game {
    public:
        Game(unsigned columns, 
                   unsigned rows, 
                   Coord lower_left, 
                   double dist_horizon, 
                   double tile_size) 
        :   _pg(columns, rows, lower_left, dist_horizon, tile_size), 
            _g (columns, rows),
            
            _os(&_g, &_pg, &_cursor),
            _gc(&_g, &_pg, &_os),
            _gb(&_g, &_pg, &_gc, &_os) { 
                update(_cursor);
                _gb.insert_Token(Token(5,7,'X'));
                _gb.insert_Token(Token(2,2,'O'));
                _gb.insert_Token(Token(2,2,'X'));
                _gb.insert_Token(Token(2,2,'X'));
                _gb.insert_Token(Token(2,2,'O'));
                _gb.insert_Token(Token(3,6,'X'));
                _gb.insert_Token(Token(3,6,'X'));
                
                _gb.insert_Token(Token(0,0,'O'));
                _gb.insert_Token(Token(1,1,'O'));
                _gb.insert_Token(Token(2,2,'X'));
                _gb.insert_Token(Token(3,3,'X'));
                _gb.insert_Token(Token(4,4,'O'));
                _gb.insert_Token(Token(5,5,'O'));
                _gb.insert_Token(Token(6,6,'X'));
                _gb.insert_Token(Token(7,7,'X'));
        }
        Grid* get_grid() {
            return &_g;
        }
        Pixel_Grid* get_pixel_grid() {
            return &_pg;
        }
        Game_Board* get_game_board() {
            return &_gb;
        }
        Cursor* get_cursor() {
            return &_cursor;
        }
        /*
        Keyboard* get_keyboard() {
            return &_keyboard;
        }*/
        void update(Cursor cursor/*, Keyboard keyboard*/) {
            _cursor = cursor;
            //_gc.set_cursor(cursor); // remove this
            _os.update(&_cursor);
            //_keyboard = keyboard;
        }
        void draw() {
            _gb.draw();
        }
        void set_dist_horizon(double dist_horizon) {
            _pg.set_dist_horizon(dist_horizon);
        }
        double get_dist_horizon() {
            return _pg.get_dist_horizon();
        }
    private:
        Cursor _cursor;
        //Keyboard _keyboard;
        Grid _g;
        Pixel_Grid _pg;
        Game_Board _gb;
        Game_Control _gc;
        Object_Space _os;
    };
}


#endif
