// File: game.hpp
#ifndef _GAME_H_
#define _GAME_H_

#include "sequence.hpp"
#include "wrapper.hpp"

#include <deque>
#include <vector>
#include <exception>
#include <cstddef>

class Game
{
  public:
    typedef std::deque<UnifiedSequence> list_type;

    ////////////////////////////////////////
    class Player : public Sequence
    {
      public:
        Player();

        virtual bool is_valid() const;
        virtual Sequence* clone() const;

        void set_last_size();

      private:
        size_t last_size;
    };

    class Bot : public Player
    {
      public:
        void make_move(Game& game);
        virtual Sequence* clone() const = 0;

      private:
        virtual void place_tiles(Game& game) = 0;
    };

    class Brute : virtual public Bot
    {
      public:
        virtual Sequence* clone() const;

      private:
        virtual void place_tiles(Game& game);
    };
    ////////////////////////////////////////

    class no_more_tiles : public std::exception
    {
      public:
        const char* what() const throw()
        {
            return "no more tiles in the random pool";
        }
    };


    Game(size_t player_count = 2, Bot* bot = 0);

    typedef list_type::iterator iterator;
    typedef list_type::const_iterator const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    Sequence& front();
    const Sequence& front() const;
    Sequence& back();
    const Sequence& back() const;

    Player::iterator player_begin(size_t n);
    Player::const_iterator player_begin(size_t n) const;
    Player::iterator player_end(size_t n);
    Player::const_iterator player_end(size_t n) const;

    Sequence& operator[](size_t n);
    const Sequence& operator[](size_t n) const;
    Sequence& at(size_t n);
    const Sequence& at(size_t n) const;


    void move_front(Sequence::iterator what, Sequence& from, Sequence& to);
    void move_back (Sequence::iterator what, Sequence& from, Sequence& to);
    void move_new  (Sequence::iterator what, Sequence& from);

    bool is_valid() const;

    void next_turn();

    size_t current_player() const;
    size_t player_count() const;

    Player& get_player(size_t n);
    const Player& get_player(size_t n) const;

    Player& get_current_player();
    const Player& get_current_player() const;

    void pick_tile() throw(no_more_tiles);
    bool no_tiles() const;

  private:
    void move(Sequence& from, Sequence& to, Sequence::iterator what, Sequence::iterator where);

    std::deque<Wrapper<Player> > players_;
    size_t current_player_;
    std::vector<Tile> great_random_;
    list_type sequences_;
};

#endif
