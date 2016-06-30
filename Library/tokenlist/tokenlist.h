// TokenList headder file
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 18th 2011

#ifndef TOKENLIST_H
#define TOKENLIST_H
#include "linked_list.h"
#include "myfunctions.h"
#include <vector>

using namespace llaae;

namespace TokenListAnconaEsselmann {
    
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
    /*
    struct cStrToken {
        cStrToken() {
            // modify so it takes a string?
            char *newToken = new char[1];
            newToken[0] = '\0';
            token = newToken;
            pos = 0;
            type = -1;
        }
        ~cStrToken() {
            delete [] token;
        }
        char *token; // DELETE IN TOKENLIST!!!!!!!!!!! OR CREATE DECONStrUCTOR
        long pos;
        int type;
        
        cStrToken *copy() {
            cStrToken *newItem = new cStrToken;
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
    
    struct intToken {
        intToken() {
            // modify so it takes a string?
            token = -1;
            pos = 0;
            type = -1;
        }
        ~intToken() {
            // empty
        }
        int token; // DELETE IN TOKENLIST!!!!!!!!!!! OR CREATE DECONStrUCTOR
        long pos;
        int type;
        
        intToken *copy() {
            intToken *newItem = new intToken;
            newItem->token = token;
            newItem->pos = pos;
            newItem->type = type;
            return newItem;
        }   
    };*/
 
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// TokenList class ////////////////////////////////////////////////
    //
    // Description: 
    class TokenList : public LinkedList<Token> {
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
        TokenList() {
            // zero argument constructor
        }
        TokenList(std::istream &ins);
        //
        TokenList(TokenList const &list) {
            // copy constructor
        }
        ~TokenList() {
            
        }
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// OVERLOADED OPERATORS ///////////////////////////////////////////////
        friend std::ostream &operator <<(std::ostream &outs, 
                                         const TokenList &list);
        //        
        friend TokenList& operator ++(TokenList &list);
        // 
        friend TokenList& operator --(TokenList &list);
        // 
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OTHER FUNKTIONS ////////////////////////////////////////////////////
        void printList(std::ostream &outs) const;
        void getTextBlock(std::istream &ins, std::vector<char> &text_block);
        /*  opens the file file_name and returns true if open was successful
         and false if unsuccessful */
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////    
    private:
        long spaceBeforeToken(std::vector<char> &text_block, long Pos) const;
        Node<Token>* getToken(std::vector<char> &text_block, long& position);
        long nextTokenPosition(std::vector<char> &text_block,long position) const;
        int  getCharacterType(char character) const;
        long lengthToken(std::vector<char> &text_block, long position) const;
        bool isWhiteSpace(char character) const;
        bool isPunktuation(char character) const;
        bool isMathOperator(char character) const;
        Node<Token>* createNode() const;        
    };
}

#endif