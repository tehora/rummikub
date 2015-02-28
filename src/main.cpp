// File: main.cpp
#include "tile.hpp"
#include "sequence.hpp"
#include "game.hpp"
#include "tile_map.hpp"

#include "lexical_cast.hpp"

#include <cstdlib>
#include <ctime>

#include <deque>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

ALLEGRO_PATH* path;

const size_t MAX_PLAYERS = 4;
ALLEGRO_COLOR BACKGROUND[MAX_PLAYERS];

const int SCREEN_W = 1280;
const int SCREEN_H =  720;

const int LEFT_MARGIN_W  = 10;
const int UPPER_MARGIN_H = 10;
const int LOWER_MARGIN_H = 10;

const int TILE_W = 30;
const int TILE_H = 45;

const int HAND_L = LEFT_MARGIN_W+20;
const int HAND_U = SCREEN_H-TILE_H-LOWER_MARGIN_H;

ALLEGRO_BITMAP* selection_frame;
ALLEGRO_BITMAP* valid_marker;
ALLEGRO_BITMAP* invalid_marker;
ALLEGRO_BITMAP* vertical_valid_marker;
ALLEGRO_BITMAP* vertical_invalid_marker;


void usage()
{
    std::cerr <<
        "\n"
        "Usage:\n"
        "    ./rummikub [ arguments ]\n\n"
        "  Arguments:\n"
        "    --help  -- print this message and exit\n"
        "    --bot   -- one player vs one bot\n"
        "    1-4     -- set player count, 2 by default\n"
              << std::endl;
}

struct TileCoords
{
    size_t x;
    size_t y;
    bool on_hand;

    TileCoords(size_t x_, size_t y_)
        : x(),
          y()
    {
        set(x_, y_);
    }

    virtual void set_x(size_t x_)
    {
        if (on_hand) {
            x = (x_ - HAND_L) / TILE_W;
        } else {
            x = (x_ - LEFT_MARGIN_W) / TILE_W;
        }
    }

    virtual void set_y(size_t y_)
    {
        on_hand = (y_ >= HAND_U);
        if (on_hand) {
            y = (y_ - HAND_U) / TILE_H;
        } else {
            y = (y_ - UPPER_MARGIN_H) / TILE_H;
        }
    }

    void set(size_t x_, size_t y_)
    {
        set_y(y_);
        set_x(x_);
    }
};

class Selection
{
  public:
    Selection()
        : active_(false),
          coords_(0,0)
    {}

    bool active() const
    {
        return active_;
    }

    void disable()
    {
        active_ = false;
    }

    Sequence& sequence()
    {
        return *sequence_;
    }
    const Sequence& sequence() const
    {
        return *sequence_;
    }

    Tile& tile()
    {
        return *tile_;
    }
    const Tile& tile() const
    {
        return *tile_;
    }

    Sequence::iterator tile_it()
    {
        return tile_;
    }
    Sequence::const_iterator tile_it() const
    {
        return tile_;
    }

    const TileCoords& coords() const
    {
        return coords_;
    }

    void set(TileCoords& new_coords, Game& game)
    {
        coords_ = new_coords;

        if (coords_.on_hand) {
            if (coords_.y > 0) {
                throw std::out_of_range("below_hand");
            }
            game.get_current_player().at(coords_.x); // bound check
            sequence_ = &game.get_current_player();
            tile_ = sequence_->begin() + coords_.x;
        } else {
            sequence_ = &game.at(coords_.x);
            sequence_->at(coords_.y); // bound check
            tile_ = sequence_->begin() + coords_.y;
        }

        active_ = true;
    }

  private:
    bool active_;
    TileCoords coords_;
    Sequence* sequence_;
    Sequence::iterator tile_;
};

void select(const TileCoords& coords)
{
    if (coords.on_hand) {
        al_draw_bitmap(selection_frame, HAND_L+coords.x*TILE_W, HAND_U, 0);
    } else {
        al_draw_bitmap(selection_frame, LEFT_MARGIN_W+coords.x*TILE_W, UPPER_MARGIN_H+coords.y*TILE_H, 0);
    }
}

void redraw(const Game& game)
{
    al_clear_to_color(BACKGROUND[game.current_player()]);

    int x = 0;
    for (Game::const_iterator game_it = game.begin(); game_it != game.end(); ++game_it, ++x) {
        if (game_it->is_valid()) {
            al_draw_bitmap(valid_marker, LEFT_MARGIN_W+x*TILE_W+5, 2, 0);
        } else {
            al_draw_bitmap(invalid_marker, LEFT_MARGIN_W+x*TILE_W+5, 2, 0);
        }

        int y = 0;
        for (Sequence::const_iterator seq_it = game_it->begin(); seq_it != game_it->end(); ++seq_it, ++y) {
            if (seq_it->color() == Tile::JANUSZ) {
                al_draw_bitmap(janusz,
                               LEFT_MARGIN_W+x*TILE_W, UPPER_MARGIN_H+y*TILE_H,
                               0);
            } else {
                try {
                    al_draw_bitmap(tile_map.at(std::make_pair(seq_it->value(), seq_it->color())),
                                   LEFT_MARGIN_W+x*TILE_W, UPPER_MARGIN_H+y*TILE_H,
                                   0);
                } catch (const std::out_of_range& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    if (game.get_current_player().is_valid() || game.no_tiles()) {
        al_draw_bitmap(vertical_invalid_marker, 17, HAND_U+5, 0);
    } else {
        al_draw_bitmap(vertical_valid_marker, 17, HAND_U+5, 0);
    }
    x = 0;
    for (Game::Player::const_iterator it = game.player_begin(game.current_player()); it != game.player_end(game.current_player()); ++it, ++x) {
        if (it->color() == Tile::JANUSZ) {
            al_draw_bitmap(janusz,
                           HAND_L+x*TILE_W, HAND_U,
                           0);
        } else {
            try {
                al_draw_bitmap(tile_map.at(std::make_pair(it->value(), it->color())),
                               HAND_L+x*TILE_W, HAND_U,
                               0);
            } catch (const std::out_of_range& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void redraw(const TileCoords& coords, const Game& game)
{
    redraw(game);
    select(coords);
}

int main(int argc, char *argv[])
{
    if (argc >= 2 && std::string(argv[1]) == "--help") {
        usage();
        return 0;
    }
    ////////////////////////////////////////////////////////////
    // init
    ////////////////////////////////////////////////////////////
    srand(time(0));

    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;

    bool doexit = false;

    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();
    al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (display == 0) {
        doexit = true;
    }
    event_queue = al_create_event_queue();
    if (event_queue == 0) {
        doexit = true;
    }
    path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    if (path == 0) {
        doexit = true;
    }
    al_append_path_component(path, "resources");

    BACKGROUND[0] = al_map_rgb(0x11,0x33,0x11);
    BACKGROUND[1] = al_map_rgb(0x33,0x11,0x11);
    BACKGROUND[2] = al_map_rgb(0x11,0x11,0x33);
    BACKGROUND[3] = al_map_rgb(0x33,0x33,0x11);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());



    if (generate_tile_map(argc > 1 && argv[1] == std::string("1")) == false) {
        doexit = true;
    }

    al_destroy_path(path);

    const int SELECTION_WIDTH = 4;
    selection_frame = al_create_bitmap(TILE_W, TILE_H);
    if (selection_frame == 0) {
        doexit = true;
    }
    al_set_target_bitmap(selection_frame);
    al_draw_rectangle(1, 1, TILE_W-1, TILE_H-1, al_map_rgb(255, 0, 0), SELECTION_WIDTH);

    const int BAR_HEIGHT = 5;
    valid_marker = al_create_bitmap(TILE_W-10, BAR_HEIGHT);
    if (valid_marker == 0) {
        doexit = true;
    }
    al_set_target_bitmap(valid_marker);
    al_clear_to_color(al_map_rgb(0,0xff,0));

    invalid_marker = al_create_bitmap(TILE_W-10, BAR_HEIGHT);
    if (invalid_marker == 0) {
        doexit = true;
    }
    al_set_target_bitmap(invalid_marker);
    al_clear_to_color(al_map_rgb(0xff,0,0));

    vertical_valid_marker = al_create_bitmap(BAR_HEIGHT, TILE_H-10);
    if (vertical_valid_marker == 0) {
        doexit = true;
    }
    al_set_target_bitmap(vertical_valid_marker);
    al_clear_to_color(al_map_rgb(0,0xff,0));

    vertical_invalid_marker = al_create_bitmap(BAR_HEIGHT, TILE_H-10);
    if (vertical_invalid_marker == 0) {
        doexit = true;
    }
    al_set_target_bitmap(vertical_invalid_marker);
    al_clear_to_color(al_map_rgb(0xff,0,0));

    al_set_target_bitmap(al_get_backbuffer(display));

    al_clear_to_color(BACKGROUND[0]);
    ////////////////////////////////////////////////////////////
    // END init
    ////////////////////////////////////////////////////////////

    Game::Bot* bot = 0;
    size_t players = 2;
    if (argc >= 2) {
        if (argv[1] == std::string("--bot")) {
            bot = new Game::Brute();
        }
        try {
            players = lexical_cast<size_t>(argv[1]);
            if (players < 1 || players > MAX_PLAYERS) {
                usage();
                doexit = true;
            }
        } catch (const bad_lexical_cast& e) {
        }
    }
    if (!doexit) {
        Game game(players, bot);
        delete bot;
        Game snapshot = game;

        try {
            redraw(game);
            al_flip_display();
        } catch (const std::out_of_range& e) {
        }
        bool doredraw = false;
        Selection selection;
        ////////////////////////////////////////
        // main event loop
        ////////////////////////////////////////
        while (doexit == false) {

            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                doexit = true;
            } else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE || ev.type == ALLEGRO_EVENT_DISPLAY_EXPOSE) {
                doredraw = true;
            }
            ////////////////////////////////////////////////////////////
            // mouse
            ////////////////////////////////////////////////////////////
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                doredraw = true;
                ////////////////////////////////////////
                // no selection
                ////////////////////////////////////////
                if (selection.active() == false) {
                    if (ev.mouse.button == 1) {
                        TileCoords coords(ev.mouse.x, ev.mouse.y);
                        try {
                            selection.set(coords, game);
                        } catch (const std::out_of_range& e) {
                        }
                    }
                }
                ////////////////////////////////////////
                // END no selection
                ////////////////////////////////////////
                // selection
                ////////////////////////////////////////
                else {
                    void (Game::*move)(Sequence::iterator, Sequence&, Sequence&) = 0;
                    if (ev.mouse.button == 1) {
                        move = &Game::move_front;
                    } else {
                        move = &Game::move_back;
                    }

                    selection.disable();

                    if (move != 0) {
                        TileCoords coords(ev.mouse.x, ev.mouse.y);
                        try {
                            if (coords.on_hand) {
                                throw std::out_of_range("on_hand");
                            } else {
                                game.at(coords.x).at(coords.y); // bound check
                                (game.*move)(selection.tile_it(), selection.sequence(), game.at(coords.x));
                            }
                        } catch (const std::out_of_range& e) {
                        }
                    }
                }
                ////////////////////////////////////////
                // END selection
                ////////////////////////////////////////
            }
            ////////////////////////////////////////////////////////////
            // END mouse
            ////////////////////////////////////////////////////////////
            // keyboard
            ////////////////////////////////////////////////////////////
            else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
                doredraw = true;
                ////////////////////////////////////////
                // common
                ////////////////////////////////////////
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_Q:
                        doexit = true;
                        break;

                    case ALLEGRO_KEY_R:
                        selection.disable();
                        if (ev.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT) {
                            game = Game(game.player_count());
                            snapshot = game;
                        } else if (ev.keyboard.modifiers == 0) {
                            game = snapshot;
                        }
                        break;
                }
                ////////////////////////////////////////
                // END common
                ////////////////////////////////////////
                // no selection
                ////////////////////////////////////////
                if (selection.active() == false) {
                    switch (ev.keyboard.keycode) {
                        case ALLEGRO_KEY_SPACE:
                            if (game.is_valid()) {
                                if (game.get_current_player().empty()) {
                                    doexit = true;
                                } else {
                                    game.next_turn();
                                    snapshot = game;
                                }
                            }
                            break;

                        case ALLEGRO_KEY_ENTER:
                            try {
                                if (game.get_current_player().is_valid() == false) {
                                    game.pick_tile();
                                    game.next_turn();
                                    snapshot = game;
                                }
                            } catch (const Game::no_more_tiles& e) {
                            }
                            break;
                    }
                }
                ////////////////////////////////////////
                // END no selection
                ////////////////////////////////////////
                // selection
                ////////////////////////////////////////
                else {
                    selection.disable();

                    switch (ev.keyboard.keycode) {
                        case ALLEGRO_KEY_1:
                            game.move_new(selection.tile_it(), selection.sequence());
                            break;
                    }
                }
                ////////////////////////////////////////
                // END selection
                ////////////////////////////////////////

            }
            ////////////////////////////////////////////////////////////
            // END keyboard
            ////////////////////////////////////////////////////////////

            if (doredraw && al_is_event_queue_empty(event_queue)) {
                if (selection.active()) {
                    redraw(selection.coords(), game);
                } else {
                    redraw(game);
                }
                al_flip_display();
                doredraw = false;
            }
        }
    }
    ////////////////////////////////////////
    // END main event loop
    ////////////////////////////////////////

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    for (std::map<std::pair<Tile::Value, Tile::Color>, ALLEGRO_BITMAP*>::iterator it = tile_map.begin(); it != tile_map.end(); ++it) {
        al_destroy_bitmap(it->second);
    }
    tile_map.clear();
    al_destroy_bitmap(selection_frame);

    al_shutdown_image_addon();
    al_shutdown_primitives_addon();

    return 0;
}
