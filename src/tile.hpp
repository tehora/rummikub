// File: tile.hpp
#ifndef _TILE_H_
#define _TILE_H_

class Tile
{
  public:
    typedef unsigned short Value;
    enum Color {
        YELLOW,
        RED,
        BLUE,
        BLACK,
        JANUSZ //special colour for Janusz
    };

    Tile(Value value, Color color);

    // getters
    Value value() const;
    Color color() const;

    bool operator==(const Tile& rhs) const;
    bool operator!=(const Tile& rhs) const;

  private:
    Value value_;
    Color color_;
};

#endif
