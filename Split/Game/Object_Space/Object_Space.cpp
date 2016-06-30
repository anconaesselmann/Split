// Object_Space implementation file

#include <iostream>
#include "Object_Space.h"

namespace aae {
    Object_Space::Object_Space(Grid* g, Pixel_Grid* pg, Cursor* c) {
        _g = g;
        _pg = pg;
        _cursor = c;
        _live_grid_coord = NULL;
        _ptr_live_token_itr = NULL;
        _active_grid_coord = NULL;
        _ptr_active_token_itr = NULL;
        update(_cursor);
    }
    void Object_Space::update(Cursor* c) {
        _cursor = c;
    }
    Coord* Object_Space::get_live_grid_coord() {
        Coord grid_coords;
        // needs to be modified
        
        
        // updating live_grid_coords
        if (_live_grid_coord == NULL)
            _live_grid_coord = new Coord;
        grid_coords = _pg->map_to_grid(*_cursor); 
        if (_g->is_in_grid(grid_coords))
            *_live_grid_coord = grid_coords;  
        else _live_grid_coord = NULL;
        
        return _live_grid_coord;
    }
    list<Token>::iterator* Object_Space::get_ptr_live_token_itr() {
        return _ptr_live_token_itr;
    }
    Coord* Object_Space::get_active_grid_coord() {
        return _active_grid_coord;
    }
    list<Token>::iterator* Object_Space::get_ptr_active_token_itr() {
        return _ptr_active_token_itr;
    }
    void Object_Space::clear_active_grid_coord() {
        if (_active_grid_coord != NULL)
            delete _active_grid_coord;
        _active_grid_coord = NULL;
    }
    void Object_Space::clear_ptr_active_token_itr() {
        if (_ptr_active_token_itr != NULL) 
            delete _ptr_active_token_itr;
        _ptr_active_token_itr = NULL;
    }
}