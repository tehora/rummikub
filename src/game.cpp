// File: game.cpp
#include "game.hpp"

#include <algorithm>
#include <typeinfo>

#include <cstddef>
#include <cassert>

Game::Game(size_t player_count, Bot* bot)
    : current_player_(0),
      great_random_(),
      sequences_()
{
    great_random_.reserve(106); // the number of tiles

    for (int i = 0; i < 2; ++i) { // add each tile two times
        //loop adding tiles to random

        for (Tile::Value value = 1; value <= 13; ++value) {
            great_random_.push_back(Tile(value, Tile::RED));
            great_random_.push_back(Tile(value, Tile::BLUE));
            great_random_.push_back(Tile(value, Tile::YELLOW));
            great_random_.push_back(Tile(value, Tile::BLACK));
        }

        //Janusz added
        great_random_.push_back(Tile(0, Tile::JANUSZ));
    }


    //make random more random
    std::random_shuffle(great_random_.begin(), great_random_.end());


    size_t i = 0;
    if (bot != 0) {
        players_.push_front(Wrapper<Player>(*bot));
        ++i;
    }
    for (; i < player_count; ++i) {
        players_.push_front(Wrapper<Player>(Player()));

    }

    //give players their tiles
    for (i = 0; i < player_count; ++i) {
        for (int j = 0; j < 14; ++j) {
            get_player(i).push_back(great_random_.back());
            great_random_.pop_back();
        }
        get_player(i).set_last_size();
    }
}


Game::iterator Game::begin()
{
    return sequences_.begin();
}
Game::const_iterator Game::begin() const
{
    return sequences_.begin();
}
Game::iterator Game::end()
{
    return sequences_.end();
}
Game::const_iterator Game::end() const
{
    return sequences_.end();
}
Sequence& Game::front()
{
    return sequences_.front();
}
const Sequence& Game::front() const
{
    return sequences_.front();
}
Sequence& Game::back()
{
    return sequences_.back();
}
const Sequence& Game::back() const
{
    return sequences_.back();
}


Game::Player::iterator Game::player_begin(size_t n)
{
    return players_[n]->begin();
}
Game::Player::const_iterator Game::player_begin(size_t n) const
{
    return players_[n]->begin();
}
Game::Player::iterator Game::player_end(size_t n)
{
    return players_[n]->end();
}
Game::Player::const_iterator Game::player_end(size_t n) const
{
    return players_[n]->end();
}

Sequence& Game::operator[](size_t n)
{
    return sequences_[n];
}
const Sequence& Game::operator[](size_t n) const
{
    return sequences_[n];
}
Sequence& Game::at(size_t n)
{
    return sequences_.at(n);
}
const Sequence& Game::at(size_t n) const
{
    return sequences_.at(n);
}

//function of moving tiles between sequences

void Game::move(Sequence& from, Sequence& to, Sequence::iterator what, Sequence::iterator where)
{
    to.splice(where, from, what);
    iterator it = begin();
    while (it != end()) {
        if (it->empty()) {
            it = sequences_.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::move_front(Sequence::iterator what, Sequence& from, Sequence& to)
{
    return move(from, to, what, to.begin());
}
void Game::move_back (Sequence::iterator what, Sequence& from, Sequence& to)
{
    return move(from, to, what, to.end());
}
void Game::move_new  (Sequence::iterator what, Sequence& from)
{
    sequences_.push_back(UnifiedSequence());
    return move(from, sequences_.back(), what, sequences_.back().end());
}

//function checking out if all the sequences are correct

bool Game::is_valid() const
{
    for (const_iterator it = begin(); it != end(); ++it) {
        if (it->is_valid() == false) {
            return false;
        }
    }
    if (get_current_player().is_valid() == false) {
        return false;
    }
    return true;
}

//updating turns

void Game::next_turn()
{
    get_current_player().set_last_size();
    current_player_ = (current_player_ + 1) % player_count();

    try {
        Bot& bot = dynamic_cast<Bot&>(get_current_player());
        bot.make_move(*this);
        return next_turn();
    } catch (const std::bad_cast& e) {
    }
}

size_t Game::current_player() const
{
    return current_player_;
}

size_t Game::player_count() const
{
    return players_.size();
}

Game::Player& Game::get_player(size_t n)
{
    return *players_.at(n);
}

const Game::Player& Game::get_player(size_t n) const
{
    return *players_.at(n);
}

Game::Player& Game::get_current_player()
{
    return get_player(current_player());
}

const Game::Player& Game::get_current_player() const
{
    return get_player(current_player());
}

void Game::pick_tile() throw(no_more_tiles)
{
    if (great_random_.empty()) {
        throw no_more_tiles();
    }

    get_current_player().push_back(great_random_.back());
    great_random_.pop_back();
}

bool Game::no_tiles() const
{
    return great_random_.empty();
}

//////////////////////////////////////////////////////////////////////

Game::Player::Player()
    : last_size(tiles_.size())
{}

bool Game::Player::is_valid() const
{
    // player has to either pick a new tile or place some tiles
    return last_size != tiles_.size();
}

Sequence* Game::Player::clone() const
{
    return new Player(*this);
}

void Game::Player::set_last_size()
{
    last_size = tiles_.size();
}
