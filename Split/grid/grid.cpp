// grid implementation file

#include <iostream>
#include "grid.h"
 
namespace aae {
    // Token function definitions
    Token::Token() {
        _face = 'O';
    }
    Token::Token(unsigned X, unsigned Y, char face) {
        _face = face;
        _location = Coord(X,Y);
    }
    unsigned Token::get_X() {
        return static_cast<unsigned>(floor(_location.X() + .5));
    }
    unsigned Token::get_Y() {
        return static_cast<unsigned>(floor(_location.Y() + .5));
    }
    void Token::c_show() {
        std::cout << _face;
    }
    
    // Grid function definitions
    Grid::Grid(unsigned columns, unsigned rows) {
        initialize(columns, rows);
    }
    void Grid::initialize(unsigned columns, unsigned rows) {
        _columns = columns;
        _rows    = rows;
        g = new list<Token>*[rows];
        for (int i = 0; i < rows; i++) {
            g[i] = new list<Token>[columns];
        }
    }
    void Grid::insert_Token(Token newToken) {
        int x = newToken.get_X();
        int y = newToken.get_Y();
        g[y][x].push_back(newToken);
    }
    Token Grid::get_Token(int x, int y) {
        if (!g[y][x].empty()) {
            return g[y][x].front();
        } else throw EMPTY_FIELD;
    }
    list<Token>* Grid::get_Token_list(int x, int y) {
        return &g[y][x];
    }
    void Grid::c_show() {
        Coord temp(0,0);
        for (int y = 0; y < _rows; y++) {
            for (int x = 0; x < _columns; x++) {
                if (g[y][x].size() > 0) {
                    g[y][x].front().c_show();
                }
                else std::cout << "-";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    bool Grid::full() {
        u_long size = 0;
        for (int x = 0; x < _columns; x++) {
            for (int y = 0; y < _rows; y++) {
                if (g[y][x].size() > 0) {
                    size++;
                }
            }
        }
        if (size >= _columns*_rows) {
            return true;
        } else return false;
    }
    bool Grid::empty(const Coord& a_Coord) {
        if (g[static_cast<int>(a_Coord.Y())][static_cast<int>(a_Coord.X())].empty()) {
            return true;
        } else return false;
    }
    /*
    bool Grid::move_Creature_to(Creature& move_this, int new_x, int new_y) {
        int old_x = move_this.get_X();
        int old_y = move_this.get_Y();
        if ((g[old_y][old_x].size() > 0) &&
            (g[new_y][new_x].size() == 0)) {
            Creature* move_creature = g[old_y][old_x].pop_head();
            move_creature->set_XY(new_x, new_y);
            insert_creature(move_creature);
            return true;
        } else return false;  
    } 
    int Grid::get_species(const Coord& a_Coord) {
        int x = static_cast<int>(a_Coord.X());
        int y = static_cast<int>(a_Coord.Y());
        if (g[y][x].size() > 0) {
            Creature* creat = g[y][x].peak_head();
            if (creat->get_face() == 'O') {
                return PREY;
            } else if (creat->get_face() == 'X') {
                return PREDATOR;
            } else if (creat->get_face() == '2') {
                return PREDATOR2;
            } else if (creat->get_face() == '3') {
                return PREDATOR3;
            } else 
                return -1; // expand for other creatures        
        } else throw EMPTY_FIELD;
    }*/
    /*
    void Grid::delete_creature(const Coord& a_Coord) {
        int x = static_cast<int>(a_Coord.X());
        int y = static_cast<int>(a_Coord.Y());
        if (!g[y][x].empty()) {
            Toden* die = g[y][x].pop_head();
            delete die;
        }
    }*/
}
