// Game_Control implementation file

#include <iostream>
#include "Game_Control.h"


namespace {
    coords _get_moves(unsigned red, unsigned green, Coord pos) {
        // make that it rejects negative automatically
        coords __moves;
        int x = static_cast<int>(pos.X());
        int y = static_cast<int>(pos.Y());
        __moves.push_back(Coord(x + red - green,
                                y));
        __moves.push_back(Coord(x + red,
                                y + green));
        __moves.push_back(Coord(x + red,
                                y - green));
        
        __moves.push_back(Coord(x - red + green,
                                y));
        __moves.push_back(Coord(x - red,
                                y + green));
        __moves.push_back(Coord(x - red,
                                y - green));
        
        __moves.push_back(Coord(x,
                                y + red - green));
        __moves.push_back(Coord(x + green,
                                y + red));
        __moves.push_back(Coord(x - green,
                                y + red));
        
        __moves.push_back(Coord(x,
                                y - red + green));
        __moves.push_back(Coord(x + green,
                                y - red));
        __moves.push_back(Coord(x - green,
                                y - red));
        return __moves;
    }
    bool _validate(Coord pos, Coord val, unsigned columns, unsigned rows) {
        if ((static_cast<int>(val.X() >= 0)) &&
            (static_cast<int>(val.Y() >= 0)) &&
            (static_cast<int>(val.X() < columns)) &&
            (static_cast<int>(val.Y() < rows)) &&
            !( // not itself
              (pos.X() == val.X()) &&
              (pos.Y() == val.Y())
              )
            ) {
            return true;
        } else return false;
    }
    coords _get_all_surrounding(Coord pos, unsigned columns, unsigned rows) {
        coords __surr;
        Coord temp;
        int x = static_cast<int>(pos.X());
        int y = static_cast<int>(pos.Y());
        temp.setXY(x+1, y);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x+1, y+1);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x, y+1);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x-1, y+1);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x-1, y);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x-1, y-1);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x, y-1);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        temp.setXY(x+1, y-1);
        if (_validate(pos, temp, columns, rows))
            __surr.push_back(temp);
        
        return __surr;
    }
}

namespace aae {
    /*
    void Game_Control::set_cursor(Cursor cursor) {
        _cursor = cursor;
    }
    Cursor Game_Control::get_cursor() {
        return _cursor;
    }*/
    
    Coord* Game_Control::get_active_stack() {
        if (_old_location.X() != -1) {
            return &_old_location;
        } else return NULL;
    }
    
    coords Game_Control::get_valid_moves(Coord pos) {
        coords __valid_moves;
        list<Token>* __token_list = _g->get_Token_list(pos);
        return _get_valid_moves(__token_list, pos, _g->get_rows(), _g->get_columns());
    }
    coords Game_Control::get_valid_splits(Coord pos, list<Token>::iterator itr) {
        coords __valid_moves;
        list<Token>* __token_list_whole = _g->get_Token_list(pos);
        list<Token> __token_list_short;
        while (itr != __token_list_whole->end()) {
            __token_list_short.push_back(*itr);
            itr++;
        }
        list<Token>* __ptr_token_list_short = &__token_list_short;
        __valid_moves = _get_valid_moves(__ptr_token_list_short, pos, _g->get_rows(), _g->get_columns());
        return __valid_moves;
    }
    coords Game_Control::get_all_valid(bool _token_is_active, list<Token>::iterator _active_token) { // remove _token_is_active and _active_token
        coords __valid_moves;
        if (_token_is_active) {
            __valid_moves = get_valid_splits(_old_location, _active_token);
        } else __valid_moves = get_valid_moves(_old_location);
        return __valid_moves;
    }
    
    coords Game_Control::_get_valid_moves(list<Token>* __token_list, Coord pos ,unsigned __rows, unsigned __columns) {
        coords __valid_moves;
        if (_old_location.X() != -1) {
            unsigned long __list_size = __token_list->size();
            unsigned __tokens_red = 0;
            unsigned __tokens_green = 0;
            if (__list_size > 1) {
                list<Token>::iterator itr;
                for (itr = __token_list->begin(); itr != __token_list->end(); itr++)
                    if (itr->get_kind() == 'X') 
                        __tokens_red++;
                    else if (itr->get_kind() == 'O') 
                        __tokens_green++;
                
                coords temp;
                temp = _get_moves(__tokens_red, __tokens_green, pos);
                for (unsigned i = 0; i < temp.size(); i++)
                    if (_validate(pos, temp[i], __columns, __rows))
                        __valid_moves.push_back(temp[i]);
            } else 
                __valid_moves = _get_all_surrounding(pos, __columns, __rows);
        }
        return __valid_moves;
    }
    
    void Game_Control::move_stack(bool& _token_is_active, list<Token>::iterator& _active_token, bool _is_on_stack) { // make both owned by this?
        
        // rewrite this so it doesn't need the cursor
        
        
        Coord grid_coords(_pg->map_to_grid(*_os->get_cursor()));
        if (_g->is_in_grid(grid_coords) && 
            !(_is_on_stack && _token_is_active) // don't move the stack when a token is highlighted and the mouse cursor is on the stack
            ) { 
            if (_os->get_cursor()->down()) {
                if (_old_location.X() == -1) {
                    _old_location = grid_coords;
                    //expand = true;
                } else if (_new_location.X() == -1) {
                    if ((_old_location.X() != grid_coords.X()) || // implement != in Coord
                        (_old_location.Y() != grid_coords.Y())) {
                        _new_location = grid_coords;
                    }
                }
                if ((_old_location.X() != -1) && (_new_location.X() != -1)) {
                    if (_token_is_active) {
                        _g->move_partial_token_list(_active_token, _old_location, _new_location);
                        _token_is_active = false;
                    } else _g->move_token_list(_old_location, _new_location);
                    _old_location.setXY(-1, -1);
                    _new_location.setXY(-1, -1);
                    //expand = false;
                }
            }   
        }
    }
}