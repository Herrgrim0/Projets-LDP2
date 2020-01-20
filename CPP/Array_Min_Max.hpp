/*Langages de programmation 2 - projet c++
* GRIMAU Romain
* 000440048
* 17/08/2018
*/

#ifndef ARRAY_MIN_MAX_HPP
#define ARRAY_MIN_MAX_HPP
#include "Min_Max.hpp"
#include "errors.hpp"

template<class T> class Array_Min_Max;
template <typename T> std::ostream& operator<<( std::ostream&, const Array_Min_Max<T>& );

template<typename T>
class Array_Min_Max: public Min_Max<T> {
private:
    T *container;
    unsigned max_len;
    unsigned front_elem, back_elem; // container index
    unsigned nbr_elem;

public:
    class Iterator: public Min_Max<T>::Iterator {
    private:
        T *elem;
        int i;
        unsigned length;

    public:
        Iterator(T*, unsigned, unsigned);
        Iterator(const Iterator&) = default;
        ~Iterator();

        inline Iterator& operator++(); //prefix returns reference
        inline Iterator operator++(int); //postfix returns values (https://en.cppreference.com/w/cpp/language/operator_incdec)
        inline Iterator& operator--();
        inline Iterator operator--(int);
        inline T& operator*() const;
        inline T* operator->() const;

        Iterator& operator=(const Iterator&) = default; //remove -Weffc++ warning

        /*operator != and == defined here to avoid linkage errors at
        compilation and declared but never defined warning*/
        inline friend bool operator== (const Iterator& it1, const Iterator& it2){
            return it1.elem == it2.elem && it1.i == it2.i;
        };
        inline friend bool operator!= (const Iterator& it1, const Iterator& it2){
            return it1.elem != it2.elem || it1.i != it2.i;
        };
    };

    Array_Min_Max(unsigned);
    Array_Min_Max(const Array_Min_Max<T>&); //copy constructor
    ~Array_Min_Max();

    T front() const override;
    T back() const override;
    void pop_front() override;
    void pop_back() override;
    void clear() override;
    size_t size() const override;
    size_t max_size() const override;
    bool empty() const override;

    Iterator insert(const T);
    Iterator begin() const;
    Iterator end() const;

    friend std::ostream& operator<< <>(std::ostream&, const Array_Min_Max&);
    Array_Min_Max<T>& operator= (const Array_Min_Max<T>&); //assignation operator
    Array_Min_Max<T>& operator=(Array_Min_Max<T>  && );
    Array_Min_Max<T> operator*(){
        return *this;
    }
};

#define temp template<typename T>

temp Array_Min_Max<T>::Array_Min_Max(unsigned n_max_len): container(new T[n_max_len+1]),
max_len(n_max_len),front_elem(0), back_elem(0), nbr_elem(0) {}

temp Array_Min_Max<T>::Array_Min_Max(const Array_Min_Max<T> &other): container(new T[other.max_size()+1]),
max_len(other.max_size()), front_elem(0), back_elem(0), nbr_elem(0) {
    if (!other.empty()){
        for(Iterator it = other.begin(); it != other.end(); ++it){
            insert(*it);
        }
        insert(*end());
    }
}

temp Array_Min_Max<T>::~Array_Min_Max() {
    delete[] container;
}

temp T Array_Min_Max<T>::front() const {
    if (!this->empty()){
        return container[front_elem];
    }
    throw EmptyContainer();
}

temp T Array_Min_Max<T>::back() const {
    if (!this->empty()){
        return container[back_elem-1];
    }
    throw EmptyContainer();
}

temp void Array_Min_Max<T>::pop_front() {
    if (!this->empty()){
        front_elem++;
        nbr_elem--;
    }
}

temp void Array_Min_Max<T>::pop_back() {
    if (!this->empty()){
        back_elem--;
        nbr_elem--;
    }
}

temp void Array_Min_Max<T>::clear() {
    front_elem = 0;
    back_elem = 0;
    nbr_elem = 0;
}

temp size_t Array_Min_Max<T>::size() const {
    return nbr_elem;
}

temp size_t Array_Min_Max<T>::max_size() const {
    return max_len;
}

temp bool Array_Min_Max<T>::empty() const {
    return begin() == end();
}

temp typename Array_Min_Max<T>::Iterator Array_Min_Max<T>::insert(const T t) {
    if (this->empty()) {
        container[front_elem] = t;
        nbr_elem++;
        back_elem++;
        return Iterator(container, front_elem, nbr_elem);
    }
    else if (nbr_elem == max_len) {
        throw FullContainer();
    }
    else {
        if (t >= container[front_elem] && front_elem > 0) {
            container[front_elem-1] = t;
            front_elem--;
            nbr_elem++;
            return Iterator(container, front_elem, nbr_elem);
        }
        else if(t <= container[back_elem-1]){
            container[back_elem] = t;
            ++nbr_elem;
            ++back_elem;
            return Iterator(container, back_elem, nbr_elem);
        }
        else {
            unsigned i = 0;
            while (container[i] > t && i < back_elem) {
                ++i;
            }
            for (unsigned j = back_elem; j > i; --j){
                container[j] = container[j-1]; // shift
            }
            container[i] = t;
            nbr_elem++;
            ++back_elem;
            return Iterator(container, i, nbr_elem);
        }
    }
}

/*begin and end are methods of the container class
source: Delannoy, Claude, Programmer en Langage C++, Paris, Eyrolles, 2017, p. 537
*/

temp typename Array_Min_Max<T>::Iterator Array_Min_Max<T>::begin() const {
    return Iterator(container, front_elem, max_len);
}

temp typename Array_Min_Max<T>::Iterator Array_Min_Max<T>::end() const {
    return Iterator(container, back_elem, max_len);
}

temp Array_Min_Max<T>& Array_Min_Max<T>::operator= (const Array_Min_Max<T> &other){
    if(this->max_size() == other.max_size()) {
        clear();
        if (!other.empty()){
            for(Iterator it = other.begin(); it != other.end(); ++it){
                insert(*it);
            }
        }
    }
    else {
        throw MaxSizeError();
    }
    return *this;
}

temp Array_Min_Max<T>& Array_Min_Max<T>::operator=(Array_Min_Max<T> &&other) {
    if(this->max_size() == other.max_size()){
        clear();
        if (!other.empty()){
            for(Iterator it = other.begin(); it != other.end(); ++it){
                insert(*it);
            }
            other.clear();
        }
    }
    else {
        throw MaxSizeError();
    }
    return *this;
}

temp std::ostream& operator<< (std::ostream &os, const Array_Min_Max<T> &container) {
    /*All methods/functions this func calls must be const because a const function
    cannot call non-const functions*/
    if (container.empty()) {
        os << "Container is empty" << '\n';
    }
    else {
        os << "number of elements: " << container.size() << '\n';
        os << "< - ";
        for(typename Array_Min_Max<T>::Iterator it = container.begin(); it != container.end(); ++it){
            os << *it << " - ";
        }
        os << ">";
    }
    return os;
}

//-----------Iterator--------------

temp Array_Min_Max<T>::Iterator::Iterator(T *new_elem, unsigned index, unsigned len):
elem(new_elem), i(index), length(len) {}

temp Array_Min_Max<T>::Iterator::~Iterator() {}

temp typename Array_Min_Max<T>::Iterator& Array_Min_Max<T>::Iterator::operator++() { // prefix
    ++i;
    i %= (length+1); //value computed is not used warning removed, modulo for circular use
    return *this;
}

temp typename Array_Min_Max<T>::Iterator Array_Min_Max<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    i++;
    i %= (length+1);
    return tmp;
}

temp typename Array_Min_Max<T>::Iterator& Array_Min_Max<T>::Iterator::operator--() {
    ((--i)+(length+1))%(length+1);
    return *this;
}

temp typename Array_Min_Max<T>::Iterator Array_Min_Max<T>::Iterator::operator--(int) {
    Iterator tmp = *this;
    ((i--)+(length+1))%(length+1);
    return  tmp;
}

temp T& Array_Min_Max<T>::Iterator::operator*() const {
    return elem[i];
}

temp T* Array_Min_Max<T>::Iterator::operator->() const {
    return &elem[i];
}

#endif
