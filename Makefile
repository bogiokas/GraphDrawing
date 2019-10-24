openGLFlags = -lglfw -lGL -lGLEW -lX11
warningFlags = -Wall -Wextra -Wshadow -Weffc++
helperObjects = Shapes.o Physics.o Graph.o DrawHelper.o GLHelper.o GraphEventHandler.o GraphBuilder.o
objects = test.o $(helperObjects)
CC = g++
version = -std=c++17

prog: $(objects)
	$(CC) $(version) $(openGLFlags) $(warningFlags) -o test $(objects) 2> build.log
	./test > out.log

test.o: test.cpp $(helperObjects)
	$(CC) $(version) -c ./test.cpp
Shapes.o: Shapes.cpp Shapes.hpp Basics.hpp
	$(CC) $(version) -c ./Shapes.cpp
Physics.o: Physics.cpp Physics.hpp Basics.hpp DrawHelper.o
	$(CC) $(version) -c ./Physics.cpp
Graph.o: Graph.cpp Graph.hpp Basics.hpp
	$(CC) $(version) -c ./Graph.cpp
DrawHelper.o: DrawHelper.cpp DrawHelper.hpp Basics.hpp
	$(CC) $(version) -c ./DrawHelper.cpp
GLHelper.o: GLHelper.cpp GLHelper.hpp
	$(CC) $(version) -c ./GLHelper.cpp
GraphEventHandler.o: GraphEventHandler.cpp GraphEventHandler.hpp
	$(CC) $(version) -c ./GraphEventHandler.cpp
GraphBuilder.o: GraphBuilder.cpp GraphBuilder.hpp
	$(CC) $(version) -c ./GraphBuilder.cpp

clean :
	rm -f $(objects)
	rm -f ./test
