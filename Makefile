INC:="/Users/mac/sdl/include"
LIB:="/Users/mac/sdl/lib"
a.out: main.cpp
	g++ main.cpp -o a.out -I $(INC) -L $(LIB) -lSDL2main -lSDL2
