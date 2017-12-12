OFLAGS = -Ofast
CPP = g++
PROJECT = parse
CFLAGS = -Wall -Wextra -std=c++11
.PHONY: clean
OBJECTS := main.o parser/Parser.o parser/first_follow/First.o parser/first_follow/Follow.o parser/grammar_reader/CFG_Reader.o parser/grammar_reader/Left_Recursion.o parser/parse_table/Parse_Table.o

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CPP) $(CFLAGS) $(OFLAGS) $(OBJECTS) -o $(PROJECT)

$(OBJECTS):%.o:%.cpp
	$(CPP) $(CFLAGS) $(OFLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf parser/*.o
	rm -rf parser/first_follow/*.o
	rm -rf parser/grammar_reader/*.o
	rm -rf parser/parse_table/*.o
	rm -rf $(PROJECT)

