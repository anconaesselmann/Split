// Item header file
// Created by Axel Esselmann on Oct 15th 2011
// Last edited: Oct 15th 2011

#ifndef INTEGER_H
#define INTEGER_H

namespace IntegerAnconaEsselmann  {
    
    struct Integer {
        int Int;
        
        Integer *copy() {
            Integer *newItem = new Integer;
            newItem->Int = Int;
            return newItem;
        }
        
    };    
    
}





#endif
