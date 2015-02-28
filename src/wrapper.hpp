// File: wrapper.hpp
#ifndef _WRAPPER_H_
#define _WRAPPER_H_

template <typename T>
class Wrapper
{
  public:
    Wrapper()
        : object_(new T)
    {}

    Wrapper(const T& object)
        : object_(&dynamic_cast<T&>(*object.clone()))
    {}

    Wrapper(const Wrapper<T>& orig)
        : object_(&dynamic_cast<T&>(*orig->clone()))
    {}

    ~Wrapper()
    {
        delete object_;
    }

    Wrapper<T>& operator=(const Wrapper<T>& orig)
    {
        if (this == &orig) {
            return *this;
        }

        T* tmp = &dynamic_cast<T&>(*orig->clone());
        delete object_;
        object_ = tmp;
        return *this;
    }

    T& operator*()
    {
        return *object_;
    }

    const T& operator*() const
    {
        return *object_;
    }

    T* operator->()
    {
        return object_;
    }

    const T* operator->() const
    {
        return object_;
    }

    operator T&()
    {
        return *object_;
    }

    operator const T&() const
    {
        return *object_;
    }

  private:
    T* object_;
};

#endif
