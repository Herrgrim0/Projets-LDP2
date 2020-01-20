/*Langages de programmation 2 - projet c++
* GRIMAU Romain
* 000440048
* 17/08/2018
*/

#ifndef MIN_MAX_HPP
#define MIN_MAX_HPP

#include <cstddef>

template<typename T>
class Min_Max {

public:
    class Iterator {
    public:
        Iterator() {}
        virtual ~Iterator() {}
    };

    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef Iterator iterator;
    typedef Iterator const_iterator;
    typedef signed int difference_type;
    typedef unsigned int size_type;

    Min_Max() {}
    virtual ~Min_Max() {}

    virtual T front() const = 0;
    virtual T back() const = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;
    virtual size_t max_size() const = 0;
    virtual bool empty() const = 0;

    Iterator insert(const T); // can't be virtual -> error: invalid covariant return type
    Iterator begin() const;
    Iterator end() const;

    T min() {return this->back();}
    T max() {return this->front();}
    void pop_min() {return this->pop_back();}
    void pop_max() {return this->pop_front();}
    Iterator cbegin() const {return this->begin();}
    Iterator cend() const {return this->end();}

};

#endif
