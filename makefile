CXX = g++
CXXFLAGS = -Wall -Wextra -g 
EXE = enigma
OBJ = enigma.o plugboard.o rotor.o reflector.o

$(EXE): $(OBJ) main.cpp
	$(CXX) $^ -o $@

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

.phony: clean
clean:
	rm -rf *.o enigma