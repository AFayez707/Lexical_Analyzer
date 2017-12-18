OFLAGS = -Ofast
CPP = g++
PROJECT = lex
CFLAGS = -Wall -Wextra -std=c++11
.PHONY: clean
OBJECTS := main.o graph/State.o graph/Graph.o dfa_generator/DFA_Generator.o dfa_reduction/DFA_Reducer.o regex-to-nfa/construct_NFA.o regex-to-nfa/Regex.o regex-to-nfa/NFA.o

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CPP) $(CFLAGS) $(OFLAGS) $(OBJECTS) -o $(PROJECT)

$(OBJECTS):%.o:%.cpp
	$(CPP) $(CFLAGS) $(OFLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf graph/*.o
	rm -rf dfa_generator/*.o
	rm -rf dfa_reduction/*.o
	rm -rf regex-to-nfa/*.o
	rm -rf $(PROJECT)
