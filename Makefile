CFLAGS =-O3
LFLAGS =-lm
POSTFIX=
ifeq  ($(DEBUG),1)
	CFLAGS =-DDEBUG=1 -g -O0
	POSTFIX=_debug_1
else
ifeq ($(DEBUG),2)
	CFLAGS =-DDEBUG=2 -g -O0
	POSTFIX=_debug_2
else 
ifeq ($(DEBUG),3)
	CFLAGS =-DDEBUG=3 -g -O0
	POSTFIX=_debug_3
endif
endif
endif

ifeq  ($(LETTERSET),1)
	CFLAGS +=-DSETOFLETTERSACCEPTED=1
else
ifeq ($(LETTERSET),2)
	CFLAGS +=-DSETOFLETTERSACCEPTED=2
else 
ifeq ($(LETTERSET),3)
	CFLAGS +=-DSETOFLETTERSACCEPTED=3
endif
endif
endif


all: bin/main1 bin/main2

main1: bin/main1

main2: bin/main2

bin/main1: src/main1.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c
	gcc -o bin/main1${POSTFIX} src/main1.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c $(CFLAGS) $(LFLAGS)

bin/main2: src/main2.c src/gestrech.c src/utils.c
	gcc -o bin/main2${POSTFIX} src/main2.c src/gestrech.c src/utils.c $(CFLAGS) $(LFLAGS)

clean:
	rm -f bin/main*