// Item header file
// Created by Axel Esselmann on Oct 15th 2011
// Last edited: Oct 15th 2011

#ifndef TOKEN_H
#define TOKEN_H
#include "myfunctions.h"

namespace TokenAnconaEsselmann  {
    
    struct Token {
        Token() {
            // modify so it takes a string?
            char *newToken = new char[1];
            newToken[0] = '\0';
            token = newToken;
            pos = 0;
            type = -1;
        }
        ~Token() {
            delete [] token;
        }
        char *token; // DELETE IN TOKENLIST!!!!!!!!!!! OR CREATE DECONStrUCTOR
        long pos;
        int type;
        
        Token *copy() {
            Token *newItem = new Token;
            int length = mfAE::cStringLength(token);
            char *newToken = new char[length];
            for (int i = 0; i < length; i++) {
                newToken[i] = token[i];
            }
            newItem->token = newToken;
            newItem->pos = pos;
            newItem->type = type;
            return newItem;
        } 
    };    
    
}
#endif