// File: sequence.cpp
#include "sequence.hpp"

#include <set>

Sequence::Sequence()
    : tiles_()
{}

Sequence::~Sequence()
{}

Sequence* Sequence::clone() const
{
    return new Sequence(*this);
}

Sequence::iterator Sequence::begin()
{
    return tiles_.begin();
}
Sequence::const_iterator Sequence::begin() const
{
    return tiles_.begin();
}
Sequence::iterator Sequence::end()
{
    return tiles_.end();
}
Sequence::const_iterator Sequence::end() const
{
    return tiles_.end();
}
Tile& Sequence::front()
{
    return tiles_.front();
}
const Tile& Sequence::front() const
{
    return tiles_.front();
}
Tile& Sequence::back()
{
    return tiles_.back();
}
const Tile& Sequence::back() const
{
    return tiles_.back();
}

Tile& Sequence::operator[](size_t n)
{
    return tiles_[n];
}
const Tile& Sequence::operator[](size_t n) const
{
    return tiles_[n];
}
Tile& Sequence::at(size_t n)
{
    return tiles_.at(n);
}
const Tile& Sequence::at(size_t n) const
{
    return tiles_.at(n);
}

void Sequence::push_back(const Tile& tile)
{
    return tiles_.push_back(tile);
}

void Sequence::push_front(const Tile& tile)
{
    return tiles_.push_front(tile);
}

void Sequence::pop_back()
{
    return tiles_.pop_back();
}

void Sequence::pop_front()
{
    return tiles_.pop_front();
}

bool Sequence::empty() const
{
    return tiles_.empty();
}

Sequence::iterator Sequence::erase(iterator what)
{
    return tiles_.erase(what);
}

void Sequence::splice(iterator where,
                      Sequence& from,
                      iterator what)
{
    tiles_.insert(where, *what);
    from.erase(what);
}

bool Sequence::is_valid() const
{
    return true;
}

//////////////////////////////////////////////////////////////////////

Sequence* NumberSequence::clone() const
{
    return new NumberSequence(*this);
}

bool NumberSequence::is_valid() const
{
    if (tiles_.empty()) {
        return true;
    }
    if (tiles_.size() < 3) {
        return false;
    }

    const_iterator first = begin();
    if (first->color() == Tile::JANUSZ) {
        ++first;
        if (first->value() == 1) { // corner case
            return false;
        }
        if (first == end()) {   // corner case
            return false;
        }
    }
    const Tile::Color sequence_color = first->color();
    Tile::Value previous_value = first->value();
    const_iterator current = first; ++current;
    while (current != end()) {
        if (previous_value >= 13) { // corner case
            return false;
        }
        if (current->color() != Tile::JANUSZ &&
            (current->value() - previous_value != 1 ||
             current->color() != sequence_color)) {
            return false;
        }
        ++previous_value;
        ++current;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////

Sequence* ColorSequence::clone() const
{
    return new ColorSequence(*this);
}

bool ColorSequence::is_valid() const
{
    if (tiles_.empty()) {
        return true;
    }
    if (tiles_.size() < 3 || tiles_.size() > 4) {
        return false;
    }

    const_iterator first = begin();
   
    //Janusz can be of any colour
    
    if (first->color() == Tile::JANUSZ) {
        ++first;
        if (first == end()) {   // corner case
            return false;
        }
    }
    const Tile::Value first_value = first->value();
    std::set<Tile::Color> colors; // encountered colors

    const_iterator current = begin();
    while (current != end()) {
        if (current->color() != Tile::JANUSZ) {
            if (current->value() != first_value) {
                return false;
            }
            if (colors.count(current->color()) != 0) {
                return false;
            }
            colors.insert(current->color());
        }
        ++current;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////

Sequence* UnifiedSequence::clone() const
{
    return new UnifiedSequence(*this);
}

bool UnifiedSequence::is_valid() const
{
    return NumberSequence::is_valid() || ColorSequence::is_valid();
}
