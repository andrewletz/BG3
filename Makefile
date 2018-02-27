CXX = g++
CFLAGS = -g -Wall
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

sfml-app: main.o
	$(CXX) $^ -o $@ $(SFML_FLAGS)
