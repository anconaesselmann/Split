// coord header file

#ifndef COORD_H
#define COORD_H

#include <iostream>
#include <vector>
#include <math.h>

namespace aae {  
    
    /* Class of x and y coordinates */
    class Coord {
    public:
        Coord(){
            _x = 0;
            _y = 0;
        }
        Coord(const Coord& a_Coord) {_x = a_Coord._x; _y = a_Coord._y;}
        Coord operator =(const Coord& a_Coord) {
            if (&a_Coord != this) _x = a_Coord._x; _y = a_Coord._y;
            return *this;
        }
        Coord(double x, double y) : _x(x), _y(y) {}
        void setX(double x) {_x = x;}
        void setY(double y) {_y = y;}
        void setXY(double x, double y) {_x = x; _y = y;}
        void setXY(const Coord& a_coord) {_x = a_coord._x; _y = a_coord._y;}
        double X() const {return _x;}
        double Y() const {return _y;}
        double norm() const {
            return sqrt(_x*_x + _y*_y);
        }
        Coord unit() const {
            double n = norm();
            return Coord(_x/n,_y/n);
        }
        Coord orth() const {
            return Coord(_y, -_x);
        }
        Coord& operator +=(const Coord& a_Coord) {
            _x += a_Coord._x;
            _y += a_Coord._y;
            return *this;
        }
        Coord& operator -=(const Coord& a_Coord) {
            _x -= a_Coord._x;
            _y -= a_Coord._y;
            return *this;
        }
        // dot product
        Coord& operator *=(const Coord& a_Coord) {
            _x *= a_Coord._x;
            _y *= a_Coord._y;
            return *this;
        }
        friend std::ostream& operator <<(std::ostream& outs, 
                                         const Coord& a_coord) {
            outs << "(" << a_coord._x << ", " << a_coord._y << ")";
            return outs;
        }
        const Coord operator +(const Coord& a_Coord) const {
            return Coord(*this) += a_Coord;
        }
        const Coord operator *(const Coord& a_Coord) const { // dot product
            return Coord(*this) *= a_Coord;
        }
        const Coord operator *(double a_number) const {
            return Coord(_x*a_number,_y*a_number);
        }
        const Coord operator /(double a_number) const {
            return Coord(_x/a_number,_y/a_number);
        }
        const Coord operator -(const Coord& a_Coord) const {
            return Coord(*this) -= a_Coord;
        }
        Coord operator -(void) const {
            return Coord(-_x,-_y);
        }
        
        bool operator==(const Coord &other) const {
            if ((_x == other._x) &&
                (_y == other._y)) {
                return true;
            } else return false;
        }
        bool operator!=(const Coord &other) const {
            return !(*this == other);
        }
    protected:
        double _x;
        double _y;
    };
    
    class Matrix {
    public:
        Matrix() {
            _columns.push_back(Coord());
        }
        Matrix(Coord a) {
            _columns.push_back(a);
        }
        Matrix(Coord a, Coord b) {
            _columns.push_back(a);
            _columns.push_back(b);
        }
        const Coord operator *=(const Coord& a_Coord) {
            return Coord(_columns[0].X() * a_Coord.X() + _columns[1].X() * a_Coord.Y(), 
                         _columns[0].Y() * a_Coord.X() + _columns[1].Y() * a_Coord.Y());
        }
        std::vector<Coord> _columns;
    };
    
    double dist(Coord a, Coord b);
    
    // returns true if b1 and b2 are on the opposite side of the line through a1 and a2
    bool opp_side(Coord a1, Coord a2, Coord b1, Coord b2);
    
    // returns the determinant of the matrix [a,b]
    double det(Coord a, Coord b);
    
    // returns the point of intersection between lines a and b
    Coord poi(Coord a1, Coord a2, Coord b1, Coord b2);
    
    Coord refl(Coord a1, Coord a2, Coord b);
    
    // return a number that is positive or negative according to what 
    // side of ab the point c is located.
    double c_to_side_of_ab(Coord a, Coord b, Coord c);
    
    // returns true if test is whithin the poligon described by the four points
    bool is_in_poligon(Coord a1, Coord a2, Coord b1, Coord b2, Coord test);
    
    // right now this works for elipses with their major axis 
    // being the x-axis. It doesn't matter if axis 1 or axis two are the length of the major axis or minor axis;
    // make more universal by passing the axes as vectors!
    bool is_in_ellipse(Coord center, Coord point, double axis1, double axis2);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //COORD 
}

#endif
