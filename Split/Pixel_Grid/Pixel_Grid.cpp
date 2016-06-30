// Pixel_Grid implementation file

#include <iostream>
#include "Pixel_Grid.h"

namespace aae {
    Pixel_Grid::Pixel_Grid(unsigned columns, 
               unsigned rows, 
               Coord lower_left, 
               double dist_horizon, 
               double tile_size) {
        _rows        = rows;
        _columns     = columns;
        _dist_h      = dist_horizon;
        _tile_size   = tile_size;
        _lower_left  = lower_left;
        double length_b = _tile_size * _rows; // why is this rows and not columns?
        _lower_right = Coord(lower_left.X() + length_b,lower_left.Y());
        
        _initialize();
    }
    void Pixel_Grid::_initialize() {
        Coord _van_p(van_p());
        double scaled_y = get_y(0); // y_coord of upper side
        _upper_left = poi(_lower_left, _van_p, Coord(0,scaled_y), Coord(1,scaled_y));
        _upper_right = poi(_lower_right, _van_p, Coord(0,scaled_y), Coord(1,scaled_y));
    }
    Coord Pixel_Grid::van_p() {
        double length_b = _tile_size * _columns;
        return Coord(_lower_left.X() + 1/2.0 * length_b, _lower_left.Y() - _dist_h);
    }
    Coord Pixel_Grid::map_to_pixel_ul(unsigned column, unsigned row) {
        double y_height = get_y(row);
        Coord a1(0,y_height);
        Coord a2(10,y_height);
        Coord b1 = get_upper_corners(column,0); // do this without guc
        Coord b2 = get_upper_corners(column,_rows);
        return poi(a1, a2, b1, b2);
    }
    Coord Pixel_Grid::map_to_pixel_center(unsigned column, unsigned row) {
        Coord ul(map_to_pixel_ul(column     , row));
        Coord ur(map_to_pixel_ul(column + 1 , row));
        Coord ll(map_to_pixel_ul(column     , row + 1));
        Coord lr(map_to_pixel_ul(column + 1 , row + 1));
        return poi(ul, lr, ur, ll);
    }
    Coord Pixel_Grid::get_upper_corners(unsigned column, unsigned row) {
        Coord grid_Coord(column, row);
        Coord left   = _lower_left  - _upper_left;
        Coord right  = _lower_right - _upper_right;
        Coord top    = _upper_right - _upper_left;
        Coord bootom = _lower_right - _lower_left;
        double y_fraction = _columns * 1 / grid_Coord.Y();
        double x_fraction = _rows    * 1 / grid_Coord.X();
        Coord y1 = _upper_left  + left   / y_fraction;
        Coord y2 = _upper_right + right  / y_fraction;
        Coord x1 = _upper_left  + top    / x_fraction;
        Coord x2 = _lower_left  + bootom / x_fraction;
        Coord ul = poi(y1, y2, x1, x2);
        return ul;
        //return Coord(ul.X(), get_y(row));
    }
    double Pixel_Grid::get_y(unsigned row) {
        double length_b = _tile_size * _columns;
        double length_s = _tile_size * _rows;
        Coord _van_p = van_p();
        Coord b = _van_p + Coord(0,length_b / 2.0 + _dist_h);
        Coord mp = poi(_van_p, Coord(_van_p.X() + 1, _van_p.Y()), _lower_right, b);
        Coord scale_point2(_lower_left.X() - length_s + length_s / _rows * row, _lower_left.Y());
        return poi(_lower_left, _van_p, mp, scale_point2).Y();
    }
    
    void Pixel_Grid::set_dist_horizon(double dist_horizon) {
        _dist_h = dist_horizon;
    }
}