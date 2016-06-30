// Created by Axel Ancona-Esselmann on 11/7/11

#include <iostream>
#include <allegro5/allegro.h>
#include "Game_Board.h"
#include "Game.h"

using aae::Token;
using aae::Coord;
using aae::Cursor;
using aae::Game_Board;
using aae::initialize_gl;
using aae::Keyboard;
using aae::Mouse;
using aae::Game;

//const unsigned grid_size = 8;
const unsigned columns = 8;
const unsigned rows    = 8;
const double tile_size = 100;
const unsigned screen_h = rows * tile_size / 2.0;
const unsigned screen_w = columns * tile_size;
const double dist_horizon = screen_h * 2.5;

int main(int argc, char **argv) {
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    initialize_gl(event_queue, timer, screen_w, screen_h);
    Keyboard kb;
    Mouse mouse;
    bool redraw = true;

    Game game(columns, 
              rows, 
              Coord(0,screen_h -20), 
              dist_horizon, 
              tile_size);
    
    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        kb.update(ev);
        mouse.update(ev);
        game.update(mouse/*, kb*/);
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            if (kb.key(KEY_UP)) {
                game.set_dist_horizon(game.get_dist_horizon() / 1.05);
            } else if (kb.key(KEY_DOWN)) {
                game.set_dist_horizon(game.get_dist_horizon() * 1.05);
            }
            game.draw();
        }
    }
    return 0;
}