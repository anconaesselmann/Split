//
//  coord.cpp
//  MyGameTest
//
//  Created by Axel Esselmann on 12/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "coord.h"

namespace aae {
    double dist(Coord a, Coord b) {
        return (a - b).norm();
    }
    bool opp_side(Coord a1, Coord a2, Coord b1, Coord b2) {
        // ones poi tests for parallel, integrate error handling
        Coord _poi = poi(a1, a2, b1, b2);
        double dist_b1_poi = dist(b1, _poi);
        double dist_b1_b2  = dist(b1, b2);
        if (dist_b1_poi < dist_b1_b2)
            return true;
        else return false;
    }
    
    double det(Coord a, Coord b) {
        return a.X() * b.Y() - a.Y() * b.X();
    }
    Coord poi(Coord a1, Coord a2, Coord b1, Coord b2) {
        // doesn't test yet if two lines are parallel
        Coord c = b1 - a1;
        Coord r_v1 = a2 - a1;
        Coord r_v2 = -(b2 - b1);
        double det_rv = det(r_v1, r_v2);
        double m = det(c, r_v2)/det_rv;
        return a1 + r_v1 * m;
    }
    Coord refl(Coord a1, Coord a2, Coord b) {
        Coord rv = a2 - a1;
        Coord rv_orth = rv.orth();
        Coord _poi = poi(a1, a2, b, b + rv_orth);
        Coord n = _poi - b;
        return _poi + n;
    }
    double c_to_side_of_ab(Coord a, Coord b, Coord c) {
        return (a.X() - c.X()) * (b.Y() - c.Y()) - (a.Y() - c.Y()) * (b.X() - c.X());
    }
    bool is_in_poligon(Coord ul, Coord ur, Coord lr, Coord ll, Coord test) {
        if ((c_to_side_of_ab(ul, ur, test) > 0) &&
            (c_to_side_of_ab(lr, ll, test) > 0) &&
            (c_to_side_of_ab(ll, ul, test) > 0) &&
            (c_to_side_of_ab(ur, lr, test) > 0)) {
            return true;
        }
        return false;
    }
    bool is_in_ellipse(Coord center, Coord point, double axis1, double axis2) {
        double __a = axis2;
        double __b = axis1;
        if (axis1 >= axis2) {
            __a = axis1;
            __b = axis2;
        }
        double __dist_center_focus = sqrt(__a * __a - __b * __b);
        Coord __F1(center.X() - __dist_center_focus, center.Y());
        Coord __F2(center.X() + __dist_center_focus, center.Y());
        
        // |P-F1| + |P-F2| < 2a => the point is in the ellipse
        double __test_length = (point - __F1).norm() + (point - __F2).norm();
        if (__test_length < 2*__a) {
            return true;
        } else return false;
    }
}