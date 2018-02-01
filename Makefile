LEX_PATH = cd lexical-analyzer
LEX_PROJECT = lex

PARSE_PATH = cd parser
PARSE_PROJECT = parse

all:
	$(PARSE_PATH) && $(MAKE) && cp $(PARSE_PROJECT) ../
	$(LEX_PATH)   && $(MAKE) && cp $(LEX_PROJECT) ../

clean:
	rm $(LEX_PROJECT)   && $(LEX_PATH)   && $(MAKE) clean
	rm $(PARSE_PROJECT) && $(PARSE_PATH) && $(MAKE) clean
