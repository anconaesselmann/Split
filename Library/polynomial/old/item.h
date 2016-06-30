// Item header file
// Created by Axel Esselmann on Oct 15th 2011
// Last edited: Oct 15th 2011

#ifndef ITEM_H
#define ITEM_H

namespace ItemAnconaEsselmann  {
    
    struct Item {
        int pow;
        int coeff;
        Item *copy() {
            Item *newItem = new Item;
            newItem->pow = pow;
            newItem->coeff = coeff;
            return newItem;
        }
        
    };    
    
}





#endif
