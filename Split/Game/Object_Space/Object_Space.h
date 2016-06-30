// Object_Space header file

#ifndef OBJECT_SPACE_H
#define OBJECT_SPACE_H
#include <list>
#include "Cursor.h"
#include "grid.h"
#include "Pixel_Grid.h"

using std::list;

namespace aae {
    class Object_Space {
    public:
        Object_Space(Grid* g, Pixel_Grid* pg, Cursor* c);
        ~Object_Space() {
            // delete all the pointer variables
            if (_active_grid_coord != NULL)
                delete _active_grid_coord;
            if (_ptr_active_token_itr != NULL) 
                delete _ptr_active_token_itr;
            if (_live_grid_coord != NULL)
                delete _live_grid_coord;
            if (_ptr_active_token_itr != NULL) 
                delete _ptr_active_token_itr;
        }
        void update(Cursor* c);
        Coord* get_live_grid_coord();
        list<Token>::iterator* get_ptr_live_token_itr();
        Coord* get_active_grid_coord();
        list<Token>::iterator* get_ptr_active_token_itr();
        void clear_active_grid_coord();
        void clear_ptr_active_token_itr();
        
        //temporary, remove this!
        Cursor* get_cursor() {
            return _cursor;
        }
    //private:
        Grid* _g;
        Pixel_Grid* _pg;
        Cursor* _cursor;
        
        Coord* _live_grid_coord;
        list<Token>::iterator* _ptr_live_token_itr;
        Coord* _active_grid_coord;
        list<Token>::iterator* _ptr_active_token_itr;
    };
}


#endif
