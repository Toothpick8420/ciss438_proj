OBJS = main.cpp
OBJ_NAME = app
all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -lsqlite3 -o $(OBJ_NAME)

run : 
	./app
