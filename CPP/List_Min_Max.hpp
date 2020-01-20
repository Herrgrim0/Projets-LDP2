/*Langages de programmation 2 - projet c++
* GRIMAU Romain
* 000440048
* 17/08/2018
*/

#ifndef LIST_MIN_MAX_HPP
#define LIST_MIN_MAX_HPP
#include "Min_Max.hpp"
#include "errors.hpp"

template<class T> class List_Min_Max;
template <typename T> std::ostream& operator<<( std::ostream&, const List_Min_Max<T>& );

template<typename T>
class List_Min_Max: public Min_Max<T> {
private:
    struct Item {
        /*Component of the double linked list*/
        T data;
        Item *next;
        Item *previous;

        Item(T n_data, Item* n_next, Item*  n_previous): data(n_data), next(n_next),
        previous(n_previous) {}

        Item(const Item&) = default;

        Item& operator=(const Item&) = default;

        friend bool operator== (const Item& item1, const Item& item2){
            return item1->data == item2->data && \
                   item1->next == item2->next && \
                   item1->previous == item2->previous;
        }

        friend bool operator!= (const Item& item1, const Item& item2) {
            return item1->data == item2->data || \
                   item1->next == item2->next || \
                   item1->previous == item2->previous;
        }
    };
    Item *head;
    unsigned nbr_elem;

public:
    class Iterator: public Min_Max<T>::Iterator {
    private:
        Item *elem;

    public:
        Iterator(Item *n_item): elem(n_item) {};
        Iterator(const Iterator&) = default;
        ~Iterator() {};

        inline Iterator& operator++();
        inline Iterator operator++(int);
        inline Iterator& operator--();
        inline Iterator operator--(int);
        inline T& operator*() const;
        inline T* operator->() const;

        Iterator& operator=(const Iterator&) = default; //remove -Weffc++ warning

        inline friend bool operator== (const Iterator& it1, const Iterator& it2) {
            return it1.elem == it2.elem;
        }

        inline friend bool operator!= (const Iterator& it1, const Iterator& it2) {
            return it1.elem != it2.elem;
        }
    };

    List_Min_Max();
    List_Min_Max(const List_Min_Max<T>&);
    ~List_Min_Max();
    T front() const override;
    T back() const override;
    void pop_front()override;
    void pop_back() override;
    void clear() override;
    size_t size() const override;
    size_t max_size() const override;
    bool empty() const override;

    Iterator insert(const T);
    Iterator begin() const;
    Iterator end() const;

    friend std::ostream& operator<< <>(std::ostream&, const List_Min_Max&);
    List_Min_Max<T>& operator= (const List_Min_Max<T>&);
    List_Min_Max<T>& operator=(List_Min_Max<T>&& other);
};

#define temp template<typename T>

temp List_Min_Max<T>::List_Min_Max(): head(new Item(T(), nullptr, nullptr)), nbr_elem(0) {
    head->next = head;
    head->previous = head;
}

temp List_Min_Max<T>::List_Min_Max(const List_Min_Max<T> &other):
head(new Item(T(), nullptr, nullptr)), nbr_elem(0){
    head->next = head;
    head->previous = head;
    if (!other.empty()) {
        for (Iterator it = other.begin();it != other.end();++it){
            insert(*it);
        }
    }
}

temp List_Min_Max<T>::~List_Min_Max() {
    clear();
    delete head;
}

temp T List_Min_Max<T>::front() const {
    if(!empty()){
        return head->next->data;
    }
    else {
        throw EmptyContainer();
    }

}

temp T List_Min_Max<T>::back() const {
    if(!empty()){
        return head->previous->data;
    }
    else {
        throw EmptyContainer();
    }

}

temp void List_Min_Max<T>::pop_front() {
    if(!empty()){
        Item *tmp = head->next; // tmp = first elem
        tmp->next->previous = head;
        head->next = tmp->next;
        delete tmp;
        --nbr_elem;
    }
    else {
        throw EmptyContainer();
    }
}

temp void List_Min_Max<T>::pop_back() {
    if(!empty()){
        Item *tmp = head->previous; // tmp = last elem
        tmp->previous->next = head;
        head->previous = tmp->previous;
        delete tmp;
        --nbr_elem;
    }
    else {
        throw EmptyContainer();
    }
}

temp void List_Min_Max<T>::clear() {
    if (!empty()){
        for(Item *current = head->next; current != head;current = current->next){
            delete current;
        }
        nbr_elem = 0;
        head->previous = head;
        head->next = head;
    }
}

temp size_t List_Min_Max<T>::size() const {
    return nbr_elem;
}

temp size_t List_Min_Max<T>::max_size() const {
    return 200;
}

temp bool List_Min_Max<T>::empty() const {
    return begin() == end();
}

temp typename List_Min_Max<T>::Iterator List_Min_Max<T>::insert(T t) {
    Item *n_item = new Item(t, nullptr, nullptr);
    if (empty()){
        head->next = n_item;
        head->previous = n_item;
        n_item->previous = head;
        n_item->next = head;
        ++nbr_elem;
    }
    else if (size() == max_size()) {
        delete n_item;
        throw FullContainer();
    }
    else {
        Item *current = head->next;
        if ( t >= current->data) { // new first elem
            n_item->next = current;
            n_item->previous = head;
            current->previous = n_item;
            head->next = n_item;
            ++nbr_elem;
        }
        else if (t <= head->previous->data){ //new last elem
            n_item->previous = head->previous;
            head->previous->next = n_item;
            n_item->next = head;
            head->previous = n_item;
            ++nbr_elem;
        }
        else {
            while(current->data > t && current != head) {
                current = current->next;
            }
            n_item->next = current;
            n_item->previous = current->previous;
            current->previous->next = n_item;
            current->previous = n_item;
            ++nbr_elem;
        }
    }
    return Iterator(n_item);
}

temp typename List_Min_Max<T>::Iterator List_Min_Max<T>::begin() const {
    return Iterator(head->next);
}

temp typename List_Min_Max<T>::Iterator List_Min_Max<T>::end() const {
    return Iterator(head);
}

temp std::ostream& operator<< (std::ostream &os, const List_Min_Max<T> &container) {
    if (container.empty()) {
        os << "Container is empty" << '\n';
    }
    else {
        os << "number of elements: " << container.size() << '\n';
        os << "< - ";
        for(typename List_Min_Max<T>::Iterator it = container.begin();it != container.end();++it){
            os << *it << " - ";
        }
        os << ">";
    }
    return os;
}

temp List_Min_Max<T>& List_Min_Max<T>::operator= (const List_Min_Max<T> &other){
    if(this.max_size() == other.max_size()) {
        clear();
        if (!other->empty()){
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

temp List_Min_Max<T> &List_Min_Max<T>::operator=(List_Min_Max<T> &&other) {
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

temp typename List_Min_Max<T>::Iterator& List_Min_Max<T>::Iterator::operator++() {
    elem = elem->next;
    return *this;
}

temp typename List_Min_Max<T>::Iterator List_Min_Max<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    elem = elem->next;
    return tmp;
}

temp typename List_Min_Max<T>::Iterator& List_Min_Max<T>::Iterator::operator--() {
    elem = elem->previous;
    return this;
}

temp typename List_Min_Max<T>::Iterator List_Min_Max<T>::Iterator::operator--(int) {
    Iterator tmp = *this;
    elem = elem->previous;
    return this;
}

temp T& List_Min_Max<T>::Iterator::operator*() const {
    return this->elem->data;
}

temp T* List_Min_Max<T>::Iterator::operator->() const {
    return &(this->elem->data);
}

#endif
