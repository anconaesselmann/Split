// al_display header file

#ifndef AL_DISPLAY_H
#define AL_DISPLAY_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sstream>
#include "My_Library_IF.h"

#include "grid.h"

using std::string;
using std::stringstream;
 
const float FPS = 10.0;



namespace aae {
    void initialize_gl(ALLEGRO_EVENT_QUEUE* &event_queue, 
                       ALLEGRO_TIMER* &timer, unsigned screen_w, unsigned screen_h);
    // uninstall all this shit
    
    ALLEGRO_COLOR COLOR_to_ALLEGRO_COLOR(COLOR color);
    ALLEGRO_FONT* FONT_to_ALLEGRO_FONT(FONT a_font);

    void draw_to_screen_buffer(); // remove clear and make it's own
    void flip_screen_buffer();
    
    void draw_pixel(float x, float y, COLOR color);
    void draw_line(Coord a, Coord b, COLOR color, float thickness);
    void draw_ellipse(Coord center, 
                      float x_rad, 
                      float y_rad, 
                      COLOR color, 
                      float thickness);
    void draw_filled_ellipse(Coord center, 
                             float x_rad, 
                             float y_rad, 
                             COLOR color);
    void draw_filled_triangle(Coord a, Coord b, Coord c, COLOR color);
    
    void draw_filled_rectangle(Coord a, Coord b, COLOR color);
    
    void draw_text(FONT a_font, COLOR color, float x, float y, string text);
    
    template <typename T>
    std::string to_string(T const& value) {
        std::stringstream sstr;
        sstr << value;
        return sstr.str();
    }
    
    class Mouse : public Cursor {
    public:
        Mouse() : Cursor(){
            
        }
        void update(ALLEGRO_EVENT ev) {
            
            if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
                    ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
                setXY(ev.mouse.x, ev.mouse.y);
            if (!_down) {
                //std::cout << "Update called: down: " << _down << ", up: " << _up << ", click: " << _click << "\n";
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    ALLEGRO_MOUSE_EVENT *mouse;
                    std::cout<<mouse->button<<"\n";
                    
                    _down = true;
                    if (_up) {
                        _click = true;
                        _up = false;
                    }
                    _updated = true;
                    //set_down();
                    
                    setXY(ev.mouse.x, ev.mouse.y);
                    
                }
            }
            if (!_up) {
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                    ALLEGRO_MOUSE_EVENT *mouse;
                    std::cout<<mouse->button<<"\n";
                    //set_up();
                    _down = false;
                    _up = true;
                    _updated = true;
                    setXY(ev.mouse.x, ev.mouse.y);
                }
            }
             
        }
    };
    
    class Keyboard { // implement key press
    public:
        Keyboard() {
            unsigned size;
            _key = new bool[size]; // change this
            for (unsigned i = 0; i < size; i++)
                _key[i] = false;
        }
        ~Keyboard() {
            delete [] _key;
        }
        bool key(KEY key) {
            return _key[key];
        }
        void update(ALLEGRO_EVENT ev) {
            if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch(ev.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        _key[KEY_UP] = true;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        _key[KEY_DOWN] = true;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        _key[KEY_LEFT] = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        _key[KEY_RIGHT] = true;
                        break;
                    case ALLEGRO_KEY_1:
                        _key[KEY_1] = true;
                        break;
                    case ALLEGRO_KEY_2:
                        _key[KEY_2] = true;
                        break;
                    case ALLEGRO_KEY_3:
                        _key[KEY_3] = true;
                        break;
                    case ALLEGRO_KEY_4:
                        _key[KEY_4] = true;
                        break;
                    case ALLEGRO_KEY_E:
                        _key[KEY_E] = true;
                        break;
                }
            } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch(ev.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        _key[KEY_UP] = false;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        _key[KEY_DOWN] = false;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        _key[KEY_LEFT] = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        _key[KEY_RIGHT] = false;
                        break;
                    case ALLEGRO_KEY_1:
                        _key[KEY_1] = false;
                        break;
                    case ALLEGRO_KEY_2:
                        _key[KEY_2] = false;
                        break;
                    case ALLEGRO_KEY_3:
                        _key[KEY_3] = false;
                        break;
                    case ALLEGRO_KEY_4:
                        _key[KEY_4] = false;
                        break;
                    case ALLEGRO_KEY_E:
                        _key[KEY_E] = false;
                        break;
                }
            }
        }
    private:
        bool* _key;
    };

}
#endif
