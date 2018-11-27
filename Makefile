run: compile
	./main && ./mainO2 && ./mainO3
compile:
	g++ -o main main.cpp
	g++ -O2 -o mainO2 main.cpp
	g++ -O3 -o mainO3 main.cpp

