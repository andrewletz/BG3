CXX = g++
CFLAGS = -std=c++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(SFMLFLAGS) $<

BG3.exe: main.cpp game.o game_state_start.o game_state_editor.o texture_manager.o
	$(CXX) $(CFLAGS) $(SFMLFLAGS) -o $@ $^

clean: 
	$(RM) $(wildcard *.exe) $(wildcard *.o)
