OBJ = main.o enigma.o helper.o plugboard.o reflector.o rotlib.o

EXE = enigma

CXX = g++

CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@


%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clear:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clear
