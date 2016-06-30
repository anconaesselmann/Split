// Game_Control header file

#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H
#include <vector>
#include <list>
#include "grid.h"
#include "Pixel_Grid.h"
#include "Object_Space.h"

#include "al_display.h"//remove this once cursor is out of this
    using aae::Cursor;

using std::vector;
using std::list;
using aae::Coord;
using aae::Grid;
using aae::Pixel_Grid;
using aae::Token;

const int NO_ACTIVE_STACK = -1;

typedef vector<Coord> coords;



namespace aae {
    class Game_Control {
    public:
        Game_Control(Grid* g, Pixel_Grid* pg, Object_Space* os) {
            _g = g;
            _pg = pg;
            _os = os;
            
            // remove and rename
            _old_location = Coord(-1,-1);
            _new_location = Coord(-1,-1);
        }
        coords get_all_valid(bool _token_is_active, list<Token>::iterator _active_token);
        coords get_valid_moves(Coord pos);
        coords get_valid_splits(Coord pos, list<Token>::iterator itr);
        
        Coord* get_active_stack();
        //void set_cursor(Cursor cursor); // remove this
        //Cursor get_cursor();
        
        void move_stack(bool& _token_is_active, list<Token>::iterator& _active_token, bool _is_on_stack);
    private:
        coords _get_valid_moves(list<Token>* __token_list, Coord pos ,unsigned __rows, unsigned __columns);
        Coord _old_location;
        Coord _new_location;
        
        Grid* _g;
        Pixel_Grid* _pg;
        Object_Space* _os;
    };
}

#endif
