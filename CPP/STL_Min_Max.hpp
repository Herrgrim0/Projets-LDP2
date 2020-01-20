/*Langages de programmation 2 - projet c++
* GRIMAU Romain
* 000440048
* 17/08/2018
*/

#ifndef STL_MIN_MAX_HPP
#define STL_MIN_MAX_HPP
#include <iostream>
#include <deque>
#include "Min_Max.hpp"
#include "errors.hpp"

template<class T> class STL_Min_Max;
template <typename T> std::ostream& operator<<(std::ostream&, const STL_Min_Max<T>&);

template<typename T>
class STL_Min_Max: public Min_Max<T>{
private:
    std::deque<T> *container;

public:
    using Iterator = typename std::deque<T>::iterator;

    STL_Min_Max();
    STL_Min_Max(const STL_Min_Max<T>&); //copy constructor
    ~STL_Min_Max();
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

    friend std::ostream& operator<< <>(std::ostream&, const STL_Min_Max&);
    STL_Min_Max<T>& operator= (const STL_Min_Max<T>&); //assignation operator
    STL_Min_Max<T>& operator=(STL_Min_Max<T>&&);
};

#define temp template<typename T>

temp STL_Min_Max<T>::STL_Min_Max(): container(new std::deque<T>) {}

temp STL_Min_Max<T>::STL_Min_Max(const STL_Min_Max<T> &other): container(new std::deque<T>) {
    if (!other.empty()){
        for(Iterator it = other.begin(); it != other.end(); ++it){
            insert(*it);
        }
    }
}

temp STL_Min_Max<T>::~STL_Min_Max() {
    delete container;
}

temp T STL_Min_Max<T>::front() const{
    if(!empty()){
        return container->front();
    }
    else {
        throw EmptyContainer();
    }
}

temp T STL_Min_Max<T>::back() const{
    if(!empty()){
        return container->back();
    }
    else {
        throw EmptyContainer();
    }
}

temp void STL_Min_Max<T>::pop_front() {
    if(!empty()){
        return container->pop_front();
    }
    else {
        throw EmptyContainer();
    }
}
temp void STL_Min_Max<T>::pop_back() {
    if(!empty()){
        return container->pop_back();
    }
    else {
        throw EmptyContainer();
    }
}

temp void STL_Min_Max<T>::clear() {
    container->clear();
}

temp size_t STL_Min_Max<T>::size() const {
    return container->size();
}

temp size_t STL_Min_Max<T>::max_size() const {
    return container->max_size();
}

temp bool STL_Min_Max<T>::empty() const {
    return container->empty();
}

temp typename STL_Min_Max<T>::Iterator STL_Min_Max<T>::insert(T t) {
    if(empty()){
        return container->insert(begin(), t);
    }
    else if(size() == max_size()){
        throw FullContainer();
    }
    else if (t < *end()){
        return container->insert(end(), t);
    }
    else {
        Iterator it = begin();
        while(it != end() && *it > t){
            ++it;
        }
        return container->insert(it, t);
    }
}

temp typename STL_Min_Max<T>::Iterator STL_Min_Max<T>::begin() const {
    return container->begin();
}

temp typename STL_Min_Max<T>::Iterator STL_Min_Max<T>::end() const {
    return container->end();
}

temp STL_Min_Max<T>& STL_Min_Max<T>::operator= (const STL_Min_Max<T> &other){
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

temp STL_Min_Max<T>& STL_Min_Max<T>::operator=(STL_Min_Max<T> &&other) {
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

temp std::ostream& operator<< (std::ostream &os, const STL_Min_Max<T> &container) {
    if (container.empty()) {
        os << "Container is empty" << '\n';
    }
    else {
        os << "number of elements: " << container.size() << '\n';
        os << "< - ";
        for(typename STL_Min_Max<T>::Iterator it = container.begin();it != container.end();++it){
            os << *it << " - ";
        }
        os << ">";
    }
    return os;
}

#endif
