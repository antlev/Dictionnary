CXXFLAGS = -g3 -gdwarf2
CCFLAGS = -g3 -gdwarf2

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: bin/main1

bin/main1: src/gestrech.c src/gestorth.c src/utils.c src/gestbib.c src/main1.c
	gcc $(DEBUG) -o bin/main1 src/gestrech.c src/gestorth.c src/utils.c src/gestbib.c src/main1.c -lm