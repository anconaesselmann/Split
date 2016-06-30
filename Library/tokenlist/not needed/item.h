// Item header file
// Created by Axel Esselmann on Oct 15th 2011
// Last edited: Oct 15th 2011

#ifndef ITEM_H
#define ITEM_H
#include "myfunctions.h"

namespace ItemAnconaEsselmann  {
    
    struct Item {
        Item() {
            // modify so it takes a string?
            char *newToken = new char[1];
            newToken[0] = '\0';
            token = newToken;
            pos = 0;
            type = -1;
        }
        ~Item() {
            delete [] token;
        }
        
        //int pow;
        //int coeff;
        
        
        char *token; // DELETE IN TOKENLIST!!!!!!!!!!! OR CREATE DECONStrUCTOR
        long pos;
        int type;
        
        Item *copy() {
            Item *newItem = new Item;
            int length = mfAE::cStringLength(token);
            char *newToken = new char[length];
            for (int i = 0; i < length; i++) {
                newToken[i] = token[i];
            }
            
            //newItem->pow = pow;
            //newItem->coeff = coeff;
            
            newItem->token = newToken;
            newItem->pos = pos;
            newItem->type = type;
            return newItem;
        }     
    };    
    
}
#endif