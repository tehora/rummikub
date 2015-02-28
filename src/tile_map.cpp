// File: tile_map.cpp
#include "tile_map.hpp"
#include <utility>
#include <allegro5/allegro.h>

std::map<std::pair<Tile::Value, Tile::Color>, ALLEGRO_BITMAP*> tile_map;

ALLEGRO_BITMAP* janusz;


//quite brute force, but it works (:

bool generate_tile_map(bool singleplayer)
{
    if (singleplayer) {
        al_set_path_filename(path, "forever_alone.png");
    } else {
        al_set_path_filename(path, "janusz.png");
    }
    janusz = al_load_bitmap( al_path_cstr( path, '/' ));

    al_set_path_filename(path, "1_red.png");
    tile_map[std::make_pair(1, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "2_red.png");
    tile_map[std::make_pair(2, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "3_red.png");
    tile_map[std::make_pair(3, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "4_red.png");
    tile_map[std::make_pair(4, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "5_red.png");
    tile_map[std::make_pair(5, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "6_red.png");
    tile_map[std::make_pair(6, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "7_red.png");
    tile_map[std::make_pair(7, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "8_red.png");
    tile_map[std::make_pair(8, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "9_red.png");
    tile_map[std::make_pair(9, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "10_red.png");
    tile_map[std::make_pair(10, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "11_red.png");
    tile_map[std::make_pair(11, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "12_red.png");
    tile_map[std::make_pair(12, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "13_red.png");
    tile_map[std::make_pair(13, Tile::RED)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "1_blue.png");
    tile_map[std::make_pair(1, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "2_blue.png");
    tile_map[std::make_pair(2, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "3_blue.png");
    tile_map[std::make_pair(3, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "4_blue.png");
    tile_map[std::make_pair(4, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "5_blue.png");
    tile_map[std::make_pair(5, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "6_blue.png");
    tile_map[std::make_pair(6, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "7_blue.png");
    tile_map[std::make_pair(7, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "8_blue.png");
    tile_map[std::make_pair(8, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "9_blue.png");
    tile_map[std::make_pair(9, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "10_blue.png");
    tile_map[std::make_pair(10, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "11_blue.png");
    tile_map[std::make_pair(11, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "12_blue.png");
    tile_map[std::make_pair(12, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "13_blue.png");
    tile_map[std::make_pair(13, Tile::BLUE)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "1_yellow.png");
    tile_map[std::make_pair(1, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "2_yellow.png");
    tile_map[std::make_pair(2, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "3_yellow.png");
    tile_map[std::make_pair(3, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "4_yellow.png");
    tile_map[std::make_pair(4, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "5_yellow.png");
    tile_map[std::make_pair(5, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "6_yellow.png");
    tile_map[std::make_pair(6, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "7_yellow.png");
    tile_map[std::make_pair(7, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "8_yellow.png");
    tile_map[std::make_pair(8, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "9_yellow.png");
    tile_map[std::make_pair(9, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "10_yellow.png");
    tile_map[std::make_pair(10, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "11_yellow.png");
    tile_map[std::make_pair(11, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "12_yellow.png");
    tile_map[std::make_pair(12, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "13_yellow.png");
    tile_map[std::make_pair(13, Tile::YELLOW)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "1_black.png");
    tile_map[std::make_pair(1, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "2_black.png");
    tile_map[std::make_pair(2, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "3_black.png");
    tile_map[std::make_pair(3, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "4_black.png");
    tile_map[std::make_pair(4, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "5_black.png");
    tile_map[std::make_pair(5, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "6_black.png");
    tile_map[std::make_pair(6, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "7_black.png");
    tile_map[std::make_pair(7, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "8_black.png");
    tile_map[std::make_pair(8, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "9_black.png");
    tile_map[std::make_pair(9, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "10_black.png");
    tile_map[std::make_pair(10, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "11_black.png");
    tile_map[std::make_pair(11, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "12_black.png");
    tile_map[std::make_pair(12, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));
    al_set_path_filename(path, "13_black.png");
    tile_map[std::make_pair(13, Tile::BLACK)] = al_load_bitmap(al_path_cstr(path, '/'));

    for (std::map<std::pair<Tile::Value, Tile::Color>, ALLEGRO_BITMAP*>::iterator it = tile_map.begin();
         it != tile_map.end();
         ++it) {
        if (it->second == 0) {
            return false;
        }
    }
    return true;
}
