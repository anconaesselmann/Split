// Item header file
// Created by Axel Esselmann on Oct 15th 2011
// Last edited: Oct 15th 2011

#ifndef POL_H
#define POL_H

namespace PolAnconaEsselmann  {
    
    struct Pol {
        int pow;
        int coeff;
        Pol *copy() {
            Pol *newItem = new Pol;
            newItem->pow = pow;
            newItem->coeff = coeff;
            return newItem;
        }
        
    };    
    
}





#endif
