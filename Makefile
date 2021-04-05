#arguments $(arg)
CCC = gcc
OPT = -lm -lSDL2 -Wall -Wextra -g -fsanitize=address -fsanitize=leak
BUILD = build
SRC = src


all : main

pre-build:
	mkdir -p build/

main : $(BUILD)/main.o $(BUILD)/gfx.o $(BUILD)/particle.o $(BUILD)/world.o
	$(CCC) -o main $(BUILD)/main.o $(BUILD)/gfx.o $(BUILD)/particle.o $(BUILD)/world.o $(OPT) 

build/main.o : $(SRC)/main.c
	$(CCC) -o $(BUILD)/main.o -c $(SRC)/main.c $(OPT) 

build/gfx.o : $(SRC)/gfx.c
	$(CCC) -o $(BUILD)/gfx.o -c $(SRC)/gfx.c $(OPT)

build/particle.o : $(SRC)/particle.c
	$(CCC) -o $(BUILD)/particle.o -c $(SRC)/particle.c $(OPT)

build/world.o : $(SRC)/world.c
	$(CCC) -o $(BUILD)/world.o -c $(SRC)/world.c $(OPT)