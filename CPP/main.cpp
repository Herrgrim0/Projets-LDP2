/*Langages de programmation 2 - projet c++
* GRIMAU Romain
* 000440048
* 17/08/2018
*/

#include <iostream>
#include <string>
#include "Array_Min_Max.hpp"
#include "List_Min_Max.hpp"
#include "STL_Min_Max.hpp"

template<typename T> using Array = Array_Min_Max<T>;
template<typename T> using List = List_Min_Max<T>;
template<typename T> using STL = STL_Min_Max<T>;

int main() {
    Array<int> A_int(10);
    Array<int> AB_int(10);
    Array<std::string> A_str(20);
    List<int> L_int;
    List<string> L_str;
    STL<double> S_dbl;
    STL<unsigned> S_uns;

    std::cout << "Utilisation de Min_Max basé sur un array:" << '\n';
    std::cout << "=========================================" << "\n\n";

    try {
        for(unsigned i = 0; i<=10; ++i){
            A_int.insert(i);
        }
    }
    catch (FullContainer& e) {
        std::cout << "error:" << e.what() << '\n';
    }
    std::cout << "Avant le swap: " << '\n';
    std::cout << "Premier conteneur: " << A_int << '\n';
    std::cout << "Deuxième conteneur: " << AB_int << '\n';
    std::swap(AB_int, A_int);
    std::cout << "Après le swap: " << '\n';
    std::cout << "Premier conteneur: " << A_int << '\n';
    std::cout << "Deuxième conteneur: " << AB_int << '\n';

    A_int.clear();

    A_str.insert("un");
    A_str.insert("deux");
    A_str.insert("trois");
    A_str.insert("quatre");
    A_str.insert("cinq");
    A_str.pop_front();
    A_str.insert("six");
    A_str.insert("sept");
    A_str.insert("huit");

    Array<std::string> A2_str(20);
    A2_str = A_str;
    std::cout << A2_str << '\n';

    std::cout << "front_elem: " << A_str.front() << '\n';
    std::cout << "back_elem: "<< A_str.back() << '\n';
    std::cout << "pop_front et pop_back" << '\n';
    A2_str.pop_max(); A2_str.pop_min();
    std::cout << "front_elem: " << A_str.front() << '\n';
    std::cout << "back_elem: "<< A_str.back() << '\n';

    std::cout << "Utilisation de Min_Max basé sur une liste circulaire:" << '\n';
    std::cout << "=====================================================" << "\n\n";

    L_int.insert(10);
    L_int.insert(82);
    L_int.insert(1);
    L_int.insert(15);
    L_int.insert(6);
    std::cout<< L_int<< '\n';
    std::cout << "min: " << L_int.min() << '\n';
    std::cout << "max: " << L_int.max() << '\n';
    std::cout << "Construction de L2 par copie: " << '\n';
    List<int> L2_int(L_int);
    std::cout << "L2: "<< L2_int << '\n';

    L_str.insert("hello");
    L_str.insert(",");
    L_str.insert("World");
    L_str.insert("!");
    std::cout << "liste circulaire avec string L1:" << L_str << '\n';
    List<std::string> L2_str;
    L2_str.insert("test");
    std::swap(L2_str, L_str);
    std::cout << "L2 après swap: " << L2_str << '\n';
    std::cout << "L1 après swap: " << L_str << '\n';

    std::cout << "Utilisation de Min_Max basé sur un conteneur de la STL:" << '\n';
    std::cout << "======================================================" << "\n\n";

    S_dbl.insert(0.00);
    S_dbl.insert(10.05);
    S_dbl.insert(50.80);
    S_dbl.insert(5.26);
    std::cout << S_dbl << '\n';
    S_dbl.insert(3.45);
    std::cout << S_dbl << '\n';

    std::cout << "Conteneur de unsigned est vide ?: "<< S_uns.empty() << '\n';
    try {
        S_uns.back();
    } catch (EmptyContainer& e) {
        std::cout << "Vous ne pouvez pas faire ça: "<< e.what() << '\n';
    }

    S_uns.insert(78);
    S_uns.insert(45);
    S_uns.insert(33);
    S_uns.insert(44);
    S_uns.insert(78);
    S_uns.insert(78);
    std::cout << "S_uns: "<< S_uns << '\n';
    STL<unsigned> S2_uns;
    S2_uns = S_uns;
    std::cout << "S2_uns: " << S2_uns << '\n';
    std::cout << "S_uns: " << S_uns << '\n';

    std::cout << "Fin." << '\n';
    return 0;
}
