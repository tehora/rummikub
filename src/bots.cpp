// File: bots.cpp
#include "game.hpp"

void Game::Bot::make_move(Game& game)
{
    try {
        place_tiles(game);
        if (!is_valid()) {
            game.pick_tile();
        }
    } catch (const no_more_tiles& e) {
        // ignore that there are no moves and skip your move -- maybe the player
        // will be smarter
    }
}

//////////////////////////////////////////////////////////////////////

void Game::Brute::place_tiles(Game& game)
{
    // try to insert all your tiles
    for (iterator my_tile = begin(); my_tile != end(); ++my_tile) {
        // into all the sequences
        for (Game::iterator sequence = game.begin(); sequence != game.end(); ++sequence) {

            // do not break the game while trying
            UnifiedSequence tmp = *sequence;

            // try to add at the beginning of a sequence
            tmp.push_back(*my_tile);
            if (tmp.is_valid()) {
                erase(my_tile);
                *sequence = tmp;
                return place_tiles(game); // restart the algorithm
            }

            // revert on failure
            tmp.pop_back();

            // try to add at the end of a sequence
            tmp.push_front(*my_tile);
            if (tmp.is_valid()) {
                erase(my_tile);
                *sequence = tmp;
                return place_tiles(game); // restart the algorithm
            }
        }
    }
}

Sequence* Game::Brute::clone() const
{
    return new Brute(*this);
}
