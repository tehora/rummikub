// File: tile.cpp
#include "tile.hpp"

Tile::Tile(Value value, Color color)
    : value_(value),
      color_(color)
{}

Tile::Value Tile::value() const
{
    return value_;
}
Tile::Color Tile::color() const
{
    return color_;
}

bool Tile::operator==(const Tile& rhs) const
{
    return (this->value() == rhs.value() &&
            this->color() == rhs.color());
}
bool Tile::operator!=(const Tile& rhs) const
{
    return !(*this == rhs);
}
