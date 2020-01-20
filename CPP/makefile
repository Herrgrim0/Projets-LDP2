#Langages de programmation 2 - projet c++
# GRIMAU Romain
# 000440048
# 17/08/2018

flags = -std=c++17 -masm=intel -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override

all: Min_Max.o Array_Min_Max.o main.o test.out List_Min_Max.o STL_Min_Max.o

Min_Max.o: Min_Max.cpp Min_Max.hpp
	touch Min_Max.o
	g++ $(flags) -c -o $@ $<

List_Min_Max.o: List_Min_Max.cpp List_Min_Max.hpp Min_Max.hpp errors.hpp
	touch List_Min_Max.o # added else compile error: no such file or directory
	g++ $(flags) -c -o $@ $<

Array_Min_Max.o: Array_Min_Max.cpp Array_Min_Max.hpp Min_Max.hpp errors.hpp
	touch Array_Min_Max.o
	g++ $(flags) -c -o $@ $<

STL_Min_Max.o: STL_Min_Max.cpp STL_Min_Max.hpp Min_Max.hpp errors.hpp
	touch STL_Min_Max.o
	g++ $(flags) -c -o $@ $<

main.o: main.cpp Array_Min_Max.hpp Min_Max.hpp
	touch main.o
	g++ $(flags) $< -c -o $@

test.out: main.o Min_Max.o Array_Min_Max.o List_Min_Max.o # STL_Min_Max.o
	touch test.out
	g++ $(flags) $^ -o $@

clean:
	rm -rf *.gch *.o


#add -o everywhere to avoid: linker input file unused because linking not done warning
