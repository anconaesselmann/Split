// Pixel_Grid header file

#ifndef MyGameTest_Pixel_Grid_h
#define MyGameTest_Pixel_Grid_h
#include "coord.h"

namespace aae {
    class Pixel_Grid {
    public:
        Pixel_Grid(unsigned columns, 
                   unsigned rows, 
                   Coord lower_left, 
                   double dist_horizon, 
                   double tile_size);
        Coord van_p();
        
        // maps proportionally to upper left corner
        Coord map_to_pixel_ul(unsigned column, unsigned row);
        Coord map_to_pixel_center(unsigned column, unsigned row);
        Coord map_to_grid(Coord pixel_coord) {
            Coord grid_coord(-1, -1);
            Coord a;
            Coord b;
            int i;
            
            for (i = _columns; i >= 0; i--) {
                a = map_to_pixel_ul(i, 1);
                b = map_to_pixel_ul(i, 0);
                
                if (c_to_side_of_ab(a, b, pixel_coord) > 0) {
                    grid_coord.setX(i);
                    break;
                }
            }
            for (i = _rows; i >= 0; i--) {
                a = map_to_pixel_ul(1, i);
                b = map_to_pixel_ul(0, i);
                
                if (c_to_side_of_ab(a, b, pixel_coord) < 0) {
                    grid_coord.setY(i);
                    break;
                }
            }
            return grid_coord;
        }

        Coord get_upper_corners(unsigned column, unsigned row);
        double get_y(unsigned row);
        void   set_dist_horizon(double dist_horizon);
        double get_dist_horizon() {
            return _dist_h;
        }
    private:
        void _initialize();
        
        Coord _upper_left;
        Coord _upper_right;
        Coord _lower_left;
        Coord _lower_right;
        unsigned _rows;
        unsigned _columns;
        double _dist_h;
        double _tile_size;
    }; 
}

#endif
