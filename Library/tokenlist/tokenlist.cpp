// TokenList implementation file    
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 16th 2011

#include <iostream>
#include "tokenlist.h"
#include "linked_list.h"
using namespace llaae;
// breaks:
// last token negative and longer than 2


namespace TokenListAnconaEsselmann {
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
    TokenList::TokenList(std::istream &ins) {
        std::vector<char>text_block;
        getTextBlock(ins, text_block);
        char temp;
        for (int i=0; i < text_block.size(); i++) {
            temp = text_block[i];
        }
        long position = 0;
        while (position < text_block.size()) {
            push_head(*getToken(text_block, position));
        }
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// OVERLOADED OPERATORS ///////////////////////////////////////////////
    std::ostream &operator <<(std::ostream &outs, 
                              const TokenList &list) {
        list.printList(outs);
        return outs;
    }
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// OTHER FUNKTIONS ////////////////////////////////////////////////////
    void TokenList::printList(std::ostream &outs) const {
        Node<Token> **NodePtrAr;
        unsigned long ls = size();
        NodePtrAr = new Node<Token>*[ls];
        NodePtrAr[0] = getHead();
        for (int i = 1; i < ls; i++) {
            NodePtrAr[i] = NodePtrAr[i-1]->next;
        }
        for (int i = ls -1; i >= 0; i--) {
            outs << NodePtrAr[i]->item->type << ": ";
            outs << NodePtrAr[i]->item->token;
            outs  << "\n";
        }
        delete [] NodePtrAr;
    }
    void TokenList::getTextBlock(std::istream &ins, std::vector<char> &text_block) {
        using namespace std;
        char next;
        long pos = 0;
        ins.get(next);
        while((! ins.eof()) && (next != '\n')) { // only takes one line
            text_block.push_back(next);
            pos++;
            ins.get(next);
        }
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   
    /// PRIVATE ////////////////////////////////////////////////////////////////
    long TokenList::spaceBeforeToken(std::vector<char> &text_block, long Pos) const {
        /*  Retrieves the position of first character of the next token in the array text_block 
         Calls: isWhiteSpace */
        int seperation = 1;
        bool quit = false;
        
        while ((isWhiteSpace(text_block[Pos - seperation])) && (quit == false)) {
            if ((Pos - seperation)>0) {
                seperation++;
            } else quit = true;
        }
        seperation--;
        return seperation;
    }
    Node<Token>* TokenList::getToken(std::vector<char> &text_block, long& position) {
        // updated, returns pointer to item
        long length_token = lengthToken(text_block, position);
        Node<Token> *newToken = new Node<Token>;
        newToken = createNode(); // is this necessary?????
        delete newToken->item->token;
        char *token = new char[length_token + 1];
        for (int i = 0; i < length_token; i++) {
            newToken->item->token[i] = text_block[position + i];
        }
        newToken->item->token[length_token] = '\0';
        newToken->item->token = token;
        // samples the last character of the token for typing it 
        // (this way negative numbers are recognized as numbers, 
        // as opposed to mathematical operators)
        newToken->item->type = getCharacterType(token[length_token - 1]); 
        position = nextTokenPosition(text_block, position + length_token);
        newToken->item->pos = position;
        return newToken;
    }
    long TokenList::nextTokenPosition(std::vector<char> &text_block, long position) const {
        /*  Retrieves the position of first character of the next token in the array text_block 
         Calls: isWhiteSpace */
        int seperation = 0;
        while (isWhiteSpace(text_block[seperation + position])) {
            seperation++;
        }
        return seperation + position;
    }
    int  TokenList::getCharacterType(char character)const {
        /*  retrieves
         0 if the character is a letter //how am I going to do this????
         1 if the character is a number
         2 if the character is punktuation
         3 if other 
         Calls: isPunktuation */
        if (isdigit(character)) {
            return 1;
        } else if (isPunktuation(character)) {
            return 2;
        } else if (islower(character) || isupper(character)) {
            return 0;
        } else if (isMathOperator(character)) {
            return 4;
        } else return 3;
    }
    long TokenList::lengthToken(std::vector<char> &text_block, long position) const {
        /*  finds the length of the token at positon in text_block and returns the 
         number of characters, until the token is terminated by either a white 
         space character or punktuation. 
         Calls: getCharacterType */
        char next;
        int char_type = getCharacterType(text_block[position]);
        long tolken_length = 1;
        // not working
        if (char_type == 4) {
            if ( (text_block[position] == '-') && ( getCharacterType(text_block[position+1]) != 1) ) {
                tolken_length = 1;
            }
        }
        if ( (char_type == 2) || (char_type == 3) ) {
            tolken_length = 1;
        } if ( (text_block[position] == '-') && ( getCharacterType(text_block[position+1]) == 1)) {
            // catches negative numbers
            tolken_length++;
            do {
                next = text_block[position + tolken_length];
                tolken_length++;
            } while ( ((tolken_length + position) < text_block.size()) && (getCharacterType(next) == 1) );
            tolken_length--;
        } else {
            do {
                next = text_block[position + tolken_length];
                tolken_length++;
            } while ( ((tolken_length + position) <= text_block.size()) && (char_type == getCharacterType(next)) );
            tolken_length--;
        }
        return tolken_length;
    }
    bool TokenList::isWhiteSpace(char character) const {
        // returns true if character is a whitespace character 
        
        if ( (character == ' ') ||
            (character == '\n') ||
            (character == '\t') ||
            (character == '\v') ||
            (character == '\f') ||
            (character == '\r')
            ) {
            return true;
        } else {
            return false;
        }
    }
    bool TokenList::isPunktuation(char character) const {
        // returns true if character is punktuation 
        
        if ( (character == '.') ||
            (character == ',') ||
            (character == '?') ||
            (character == '!') ||
            (character == ':') ||
            (character == '\'') ||
            (character == '"') ||
            (character == ';')
            ) {
            return true;
        } else {
            return false;
        }
    }
    bool TokenList::isMathOperator(char character) const {
        // returns true if mathematical operator 
        
        if ( (character == '+') ||
            (character == '-') ||
            (character == '*') ||
            (character == '/') ||
            (character == '<') ||
            (character == '>') ||
            (character == '(') || //turn into own category
            (character == ')') || //turn into own category
            (character == '^') || //turn into own category
            (character == '=') 
            ) {
            return true;
        } else {
            return false;
        }
    }
    Node<Token>* TokenList::createNode() const {
        Node<Token> *newNode = new Node<Token>;
        Token *newItem = new Token;
        newNode->item = newItem;
        newNode->next = NULL;
        return newNode;
    }
}








