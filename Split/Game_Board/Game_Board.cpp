// Game_Board implementation file

#include <iostream>
#include "Game_Board.h"
#include "Game_Control.h"

namespace {
    
}

namespace aae {
    void Game_Board::insert_Token(Token newToken) {
        _g->insert_Token(newToken);
    }

    void Game_Board::_draw_stack(list<Token>* token_list, 
                                unsigned column, 
                                unsigned row) {
        Coord* __active_stack = _gc->get_active_stack();
        if (!token_list->empty()) {
            double x_rad = _tile_width_in_persp(column, row) / 2.3;
            double y_rad = _tile_hight_in_persp(column, row) / 2.3;
            double indiv_hight = _tile_hight_in_persp(column, row) / 5.0; // this is wrong
            Coord rad_loc = _pg->map_to_pixel_center(column,row);
            double y_rad_adj;
            COLOR __color;
            COLOR __highlight;
            int i = 0;
            list<Token>::iterator itr;
            

            // draw highlight for active tile and set higth to 2X
            if (__active_stack != NULL) {
                if ((column == __active_stack->X()) && // write == for Coord
                    (row    == __active_stack->Y())) {
                    indiv_hight *= 2;
                    _draw_colorful_tile(*__active_stack, COLOR_TILE_ACTIVE);
                }
            }

            for (itr = token_list->begin(); itr != token_list->end(); itr++) {
                
                y_rad_adj = i * indiv_hight;
                Coord center(rad_loc.X(), rad_loc.Y() - y_rad_adj);
                Coord center2(rad_loc.X(),rad_loc.Y() - (y_rad_adj+ indiv_hight));
                Coord ll(center.X() - (x_rad), center.Y());
                Coord ul(center2.X() - (x_rad), center2.Y());
                Coord lr(center.X() + (x_rad), center.Y());
                Coord ur(center2.X() + (x_rad), center2.Y());
                
                _set_token_color(itr, __color, __highlight);
                
                
                draw_ellipse(center, x_rad, y_rad, COLOR_TOKEN_OUTLINE, 2);
                
                
                if (is_in_poligon(ul, ur, lr, ll, *_os->get_cursor())) {        // cursor
                    _is_on_stack = true;
                }
                
                if (((__active_stack != NULL) && // draw highlighted token
                    (column == __active_stack->X()) &&
                    (row    == __active_stack->Y())    &&
                    (is_in_poligon(ul, ur, lr, ll, *_os->get_cursor()))) ||     // cursor
                    (itr == _active_token)){
                    draw_filled_ellipse(center, x_rad, y_rad, __highlight);
                    draw_filled_rectangle(ll, ur, __highlight);
                    draw_ellipse(center2, x_rad, y_rad, COLOR_TOKEN_OUTLINE, 2);
                    draw_filled_ellipse(center2, x_rad, y_rad, __highlight);
                    if (_os->get_cursor()->down()) {                            // cursor
                        _active_token = itr;
                        _token_is_active = true;
                    }
                } else { // draw regular token
                    draw_filled_ellipse(center, x_rad, y_rad, __color);
                    draw_filled_rectangle(ll, ur, __color);
                    draw_ellipse(center2, x_rad, y_rad, COLOR_TOKEN_OUTLINE, 2);
                    draw_filled_ellipse(center2, x_rad, y_rad, __color);
                }

                draw_line(ul, ll, COLOR_TOKEN_OUTLINE, 1);
                draw_line(ur, lr, COLOR_TOKEN_OUTLINE, 1);
                
                i++;
                
            }
        }
    }
    void Game_Board::_set_token_color(list<Token>::iterator itr, 
                                      COLOR& token_color, 
                                      COLOR& token_highl_color) {
        if (itr->get_kind() == 'X') {
            token_color = COLOR_TOKEN_X;
            token_highl_color = COLOR_TOKEN_X_HIGHLIGHT;
        } else if (itr->get_kind() == 'O') {
            token_color = COLOR_TOKEN_O;
            token_highl_color = COLOR_TOKEN_O_HIGHLIGHT;
        }
    }
    
    void Game_Board::draw() {
        Coord* grid_coords = _os->get_live_grid_coord();
        
        draw_to_screen_buffer();
        _draw_board(); 
        if (grid_coords != NULL) 
            _draw_colorful_tile(*grid_coords, COLOR_TILE_LIVE); // highlight tile with cursor
        
        _is_on_stack = false; // does this belong here?
        
        _draw_valid_moves(); // draw valid moves highlights
        _draw_stacks();
        _draw_info();// draw textual information
        
        draw_pixel(_pg->van_p().X(), _pg->van_p().Y(), COLOR_RED); // van point
        
        flip_screen_buffer();
        
        
        
        //this needs to go somewhere other than draw
        // moving a stack or a parital stack
        _gc->move_stack(_token_is_active, _active_token, _is_on_stack); // change
    }
    void Game_Board::_draw_colorful_tile(Coord grid_coords, COLOR color) {
        if (!_is_on_stack) {
            if (_g->is_in_grid(grid_coords)) {
                Coord __ul = _pg->map_to_pixel_ul(grid_coords.X(),     grid_coords.Y());
                Coord __ll = _pg->map_to_pixel_ul(grid_coords.X(),     grid_coords.Y() + 1);
                Coord __lr = _pg->map_to_pixel_ul(grid_coords.X() + 1, grid_coords.Y() + 1);
                Coord __ur = _pg->map_to_pixel_ul(grid_coords.X() + 1, grid_coords.Y());
                draw_filled_triangle(__ul, __ur, __lr, color);
                draw_filled_triangle(__lr, __ll, __ul, color);
            }
        }
    }
    void Game_Board::_draw_board() {
        // draw tiles
        for (int i = 0; i <= _g->get_rows(); i++)
            draw_line(_pg->map_to_pixel_ul(0,i), 
                      _pg->map_to_pixel_ul(_g->get_columns(),i),
                      COLOR_BOARD_LINES,
                      2);
        for (int i = 0; i <= _g->get_columns(); i++)
            draw_line(_pg->map_to_pixel_ul(i,0), 
                      _pg->map_to_pixel_ul(i,_g->get_rows()),
                      COLOR_BOARD_LINES,
                      2);
    }
    void Game_Board::_draw_valid_moves() {
        coords __valid_moves = _gc->get_all_valid(_token_is_active, _active_token); //change

        for (unsigned i = 0; i < __valid_moves.size(); i++) {
            _draw_colorful_tile(__valid_moves[i], COLOR_VALID_MOVES);
        }
    }
    void Game_Board::_draw_info() {
        Coord* grid_coords = _os->get_live_grid_coord();
        
        if (grid_coords != NULL)
            Text_Box tb(15, 20, to_string(*grid_coords));
        

        Text_Box tb3(15, 80, to_string(_is_on_stack));
    }
    void Game_Board::_draw_stacks() {
        for (int x = 0; x < _g->get_columns(); x++)
            for (int y = 0; y < _g->get_rows(); y++) {
                list<Token>* token_list = _g->get_Token_list(x,y);
                if (!token_list->empty()) 
                    _draw_stack(token_list, x, y);
            }
    }  
    
    
    
    double Game_Board::_tile_hight_in_persp(unsigned column, unsigned row) {
        Coord __ul = _pg->map_to_pixel_ul(column,     row);
        Coord __ll = _pg->map_to_pixel_ul(column,     row + 1);
        Coord tile_left(__ul - __ll);
        return tile_left.norm();;
    }
    double Game_Board::_tile_width_in_persp(unsigned column, unsigned row) {
        Coord __ll = _pg->map_to_pixel_ul(column,     row + 1);
        Coord __lr = _pg->map_to_pixel_ul(column + 1, row + 1);
        Coord tile_bottom(__ll - __lr);
        return tile_bottom.norm();;
    }
}