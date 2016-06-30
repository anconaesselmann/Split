// Game_Board header file
// needs a file that serves as a link to a graphics library

#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "grid.h"
#include "Pixel_Grid.h"
#include "Game_Control.h"
#include "Object_Space.h"
#include "al_display.h" // for now this is the interface to the graphics library

const COLOR COLOR_TILE_LIVE = COLOR_WHITE;
const COLOR COLOR_TILE_ACTIVE = COLOR_BLUE;
const COLOR COLOR_TOKEN_OUTLINE = COLOR_YELLOW;
const COLOR COLOR_TOKEN_X = COLOR_RED_DARK;
const COLOR COLOR_TOKEN_X_HIGHLIGHT = COLOR_RED;
const COLOR COLOR_TOKEN_O = COLOR_GREEN_DARK;
const COLOR COLOR_TOKEN_O_HIGHLIGHT = COLOR_GREEN;
const COLOR COLOR_VALID_MOVES = COLOR_YELLOW;
const COLOR COLOR_BOARD_LINES = COLOR_WHITE;

namespace aae {
    class Game_Board {
    public:
        Game_Board(Grid* g, 
                   Pixel_Grid* pg, 
                   Game_Control* gc, 
                   Object_Space* os) 
            : _g(g), _pg(pg), _gc(gc), _os(os) {
            // these should be owned by someone else
            _token_is_active = false;
            _is_on_stack = false;
        }
        void insert_Token(Token newToken);
        void draw();
    private:
        void _set_token_color(list<Token>::iterator itr, COLOR& token_color, COLOR& token_highl_color);
        double _tile_width_in_persp(unsigned column, unsigned row);
        double _tile_hight_in_persp(unsigned column, unsigned row);
        void _draw_colorful_tile(Coord grid_coords, COLOR color);
        
        // drawing
        void _draw_board();
        
        // _draw_board calls:
        void _draw_valid_moves();
        void _draw_stack(list<Token>* token_list, 
                         unsigned column, 
                         unsigned row);
        void _draw_stacks();
        void _draw_info();
        
        Grid* _g;
        Pixel_Grid* _pg;
        Game_Control* _gc;
        Object_Space* _os;
        
        
        list<Token>::iterator _active_token;
        bool _token_is_active;
        bool _is_on_stack;

    };
}

#endif
