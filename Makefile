all: compile run

compile:
	g++ -o main main.cpp
run:
	.\main.exe