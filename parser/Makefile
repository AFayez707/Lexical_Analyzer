OFLAGS = -O3
CPP = g++
PROJECT = parse
CFLAGS = -Wall -Wextra -std=c++11
.PHONY: clean
OBJECTS := main.o Parser.o first_follow/First.o first_follow/Follow.o grammar_reader/CFG_Reader.o grammar_reader/Left_Recursion.o parse_table/Parse_Table.o

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CPP) $(CFLAGS) $(OFLAGS) $(OBJECTS) -o $(PROJECT)

$(OBJECTS):%.o:%.cpp
	$(CPP) $(CFLAGS) $(OFLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf first_follow/*.o
	rm -rf grammar_reader/*.o
	rm -rf parse_table/*.o
	rm -rf $(PROJECT)
