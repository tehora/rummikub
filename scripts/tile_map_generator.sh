#!/bin/zsh

for c in red blue yellow black; do
    for v in {1..13}; do
        echo "al_set_path_filename(path, \"${v}_${c}.png\");"
        echo "tile_map[std::make_pair($v, Tile::${c:u})] = al_load_bitmap(al_path_cstr(path, '/'));"
    done
done
