// File: lexical_cast.hpp
#ifndef _LEXICAL_CAST_H_
#define _LEXICAL_CAST_H_

#include <sstream>

class bad_lexical_cast : public std::exception
{
  public:
    const char* what() const throw()
    {
        return "bad_lexical_cast";
    }
};

template <typename T1, typename T2>
T1 lexical_cast(T2 source) throw(bad_lexical_cast) {
    T1 result;
    std::stringstream stream;
    stream << source;
    stream >> result;
    if (stream.fail() || !stream.eof()) {
        throw bad_lexical_cast();
    }
    return result;
}

#endif
