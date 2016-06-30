//  al_display implementation file

#include <iostream>
#include "al_display.h"

namespace aae {
    static ALLEGRO_DISPLAY* display;
    static ALLEGRO_FONT* font;
    
    ALLEGRO_COLOR COLOR_to_ALLEGRO_COLOR(COLOR color) {
        ALLEGRO_COLOR _color;
        switch (color) {
            case COLOR_RED:
                _color = al_map_rgb(255, 0, 0);
                break;
            case COLOR_GREEN:
                _color = al_map_rgb(0, 255, 0);
                break;
            case COLOR_BLUE:
                _color = al_map_rgb(0, 0, 255);
                break;
            case COLOR_BLACK:
                _color = al_map_rgb(0, 0, 0);
                break;
            case COLOR_WHITE:
                _color = al_map_rgb(255, 255, 255);
                break;
            case COLOR_YELLOW:
                _color = al_map_rgb(255, 255, 0);
                break;
            case COLOR_GREEN_DARK:
                _color = al_map_rgb(0, 150, 0);
                break;
            case COLOR_RED_DARK:
                _color = al_map_rgb(150, 0, 0);
                break;
                
            default:
                break;
        }
        return _color;
    }
    ALLEGRO_FONT* FONT_to_ALLEGRO_FONT(FONT a_font) {
        ALLEGRO_FONT* _font;
        switch (a_font) {
            case FONT_TIMES:
                _font = font;
                break;
                
            default:
                break;
        }
        return _font;
    }
    void draw_pixel(float x, float y, COLOR color) {
        al_draw_pixel(x, y, COLOR_to_ALLEGRO_COLOR(color));
    }
    void draw_line(Coord a, Coord b, COLOR color, float thickness) {
        al_draw_line(a.X(), a.Y(), b.X(), b.Y(), COLOR_to_ALLEGRO_COLOR(color), thickness);
    }
    void draw_ellipse(Coord center, float x_rad, float y_rad, COLOR color, float thickness) {
        al_draw_ellipse(center.X(), center.Y(), x_rad, y_rad, COLOR_to_ALLEGRO_COLOR(color), thickness);
    }
    void draw_filled_ellipse(Coord center, float x_rad, float y_rad, COLOR color) {
        al_draw_filled_ellipse(center.X(), center.Y(), x_rad, y_rad, COLOR_to_ALLEGRO_COLOR(color));
    }
    void draw_filled_triangle(Coord a, Coord b, Coord c, COLOR color) {
        al_draw_filled_triangle(a.X(), a.Y(), b.X(), b.Y(), c.X(), c.Y(), COLOR_to_ALLEGRO_COLOR(color));
    }
    void draw_filled_rectangle(Coord a, Coord b, COLOR color) {
        al_draw_filled_rectangle(a.X(), a.Y(), b.X(), b.Y(), COLOR_to_ALLEGRO_COLOR(color));
    }
    void draw_to_screen_buffer() {
        al_set_target_bitmap(al_get_backbuffer(display));
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    void flip_screen_buffer() {
         al_flip_display();
    }
    
    void initialize_gl(ALLEGRO_EVENT_QUEUE* &event_queue, 
                       ALLEGRO_TIMER* &timer, unsigned screen_w, unsigned screen_h) {
        al_init();
        al_init_primitives_addon();
        al_init_font_addon();
        al_init_ttf_addon();
        display = al_create_display(screen_w, screen_h);
        const char *font_file = "times.ttf";
        font = al_load_ttf_font(font_file, 18, 0);
        if(!font) printf("Error loading \"%s\".\n", font_file);
        timer = al_create_timer(1.0 / FPS);
        event_queue = al_create_event_queue();
        al_install_keyboard();
        al_install_mouse();
        al_register_event_source(event_queue, 
                                 al_get_display_event_source(display));
        al_register_event_source(event_queue, 
                                 al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());
        al_start_timer(timer);
    }
    // uninstall all this shit
    void draw_text(FONT a_font, COLOR color, float x, float y, string text) {
        al_draw_text(FONT_to_ALLEGRO_FONT(a_font), COLOR_to_ALLEGRO_COLOR(color), x, y, 0, text.c_str());
    }
    
    
    
    
}