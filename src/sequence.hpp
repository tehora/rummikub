// File: sequence.hpp
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "tile.hpp"
#include "wrapper.hpp"

#include <deque>
#include <cstddef>

class Sequence
{
  public:
    typedef std::deque<Tile> list_type;
    typedef list_type::iterator iterator;
    typedef list_type::const_iterator const_iterator;
    Sequence();
    virtual ~Sequence();

    virtual Sequence* clone() const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    Tile& front();
    const Tile& front() const;
    Tile& back();
    const Tile& back() const;

    Tile& operator[](size_t n);
    const Tile& operator[](size_t n) const;
    Tile& at(size_t n);
    const Tile& at(size_t n) const;

    virtual bool is_valid() const;

    void push_back(const Tile& tile);
    void push_front(const Tile& tile);
    void pop_back();
    void pop_front();

    iterator erase(iterator what);
    void splice(iterator where,
                Sequence& from,
                iterator what);

    bool empty() const;

  protected:
    list_type tiles_;
};

//////////////////////////////////////////////////////////////////////

class NumberSequence : virtual public Sequence
{
  public:
    virtual bool is_valid() const;
    virtual Sequence* clone() const;
};

//////////////////////////////////////////////////////////////////////

class ColorSequence : virtual public Sequence
{
  public:
    virtual bool is_valid() const;
    virtual Sequence* clone() const;
};

//////////////////////////////////////////////////////////////////////

class UnifiedSequence : public NumberSequence, public ColorSequence
{
  public:
    virtual bool is_valid() const;
    virtual Sequence* clone() const;
};

#endif
