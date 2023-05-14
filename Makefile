test.out : main.o Genetic.o Environment.o
	g++ -o test.out main.o Genetic.o Environment.o
main.o : main.cpp
	g++ -c main.cpp
Genetic.o : Genetic.cpp
	g++ -c Genetic.cpp
Environment.o : Environment.cpp
	g++ -c Environment.cpp