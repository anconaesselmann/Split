// coord header file

#ifndef COORD_H
#define COORD_H

#include <iostream>
#include "grid.h"

namespace aae {  
    
    /* Class of x and y coordinates */
    class Coord {
    public:
        Coord(){
            x = 0;
            y = 0;
        }
        Coord(double _x, double _y) : x(_x), y(_y) {}
        void setX(double _x) {x = _x;}
        void setY(double _y) {y = _y;}
        void setXY(double _x, double _y) {x = _x; y = _y;}
        double X() const {return x;}
        double Y() const {return y;}
        friend std::ostream& operator <<(std::ostream& outs, 
                                         const Coord& a_coord) {
            outs << "(" << a_coord.x << ", " << a_coord.y << ")";
            return outs;
        }
    private:
        double x;
        double y;
    };
}

#endif
