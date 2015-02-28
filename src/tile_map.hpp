// File: tile_map.hpp
#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

#include "tile.hpp"

#include <map>
#include <utility>
#include <allegro5/allegro.h>

extern std::map<std::pair<Tile::Value, Tile::Color>, ALLEGRO_BITMAP*> tile_map;

extern ALLEGRO_BITMAP* janusz;
extern ALLEGRO_PATH* path;

bool generate_tile_map(bool singleplayer = false);

#endif
