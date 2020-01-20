/*Langages de programmation 2 - projet c++
* GRIMAU Romain
* 000440048
* 17/08/2018
*/

#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <exception>
using namespace std;

struct EmptyContainer : public exception {
   const char * what () const throw () override {
      return "Container is empty !";
   }
};

struct FullContainer : public exception {
    const char * what() const throw () override {
        return "Container is full !";
    }
};

struct MaxSizeError : public exception {
    const char * what() const throw () override {
        return "The containers don't have the same max size !";
    }
};

#endif
