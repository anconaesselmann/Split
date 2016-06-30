// grid header file

#ifndef GRID_H
#define GRID_H

#include <list>
#include <vector>
#include <math.h>
#include "coord.h"
#include "myfunctions.h"

using std::list;
using namespace mfAE;

typedef unsigned long u_long;

const int FULL_GRID = 0;
const int EMPTY_FIELD = -1;

namespace aae {
    class Token {
    public:
        Token();
        Token(unsigned X, unsigned Y, char face);
        unsigned get_X();
        unsigned get_Y();
        void set_location(Coord new_loc) {
            _location = new_loc;
        }
        void c_show();
        char get_kind() {
            return _face;
        }
    private:
        char _face;
        Coord _location;
    };
    
    class Grid {
    public:
        Grid(unsigned columns, unsigned rows);
        
        void insert_Token(Token newToken);
        
        // inserts an pointer to an existing creature
        void c_show();
        bool full();
        
        // returns the first item in the list without popping it
        Token get_Token(int x, int y);
        list<Token>* get_Token_list(int x, int y);
        list<Token>* get_Token_list(Coord loc) {
            return get_Token_list(loc.X(), loc.Y());
        }
        
        void move_token_list(Coord is_at, Coord move_to) {
            Token temp;
            list<Token>* token_list = get_Token_list(is_at);
            while (!token_list->empty()) {
                temp = token_list->front();
                token_list->pop_front();
                temp.set_location(move_to);
                insert_Token(temp);
            }
        }
        void move_partial_token_list(list<Token>::iterator &itr, Coord is_at, Coord move_to) {
            // so far it doesn't test if the iterator is valid
            Token temp;
            list<Token>* __token_list = get_Token_list(is_at);
            
            while (itr != __token_list->end()) {
                temp = *itr;
                temp.set_location(move_to);
                insert_Token(temp);
                itr = __token_list->erase(itr);
            }
            
            
        }

        bool empty(const Coord& a_Coord);
        
        bool is_in_grid(const Coord& a_Coord) {
            if ((a_Coord.X() < _columns) &&
                (a_Coord.X() >= 0)       &&
                (a_Coord.Y() < _rows)    &&
                (a_Coord.Y() >= 0)) {
                return true;
            } else return false;
        }
        unsigned get_columns() {
            return _columns;
        }
        unsigned get_rows() {
            return _rows;
        }
    protected:
        void initialize(unsigned columns, unsigned rows);
        unsigned _columns;
        unsigned _rows;
        
        list<Token>** g;
    };
}
#endif
