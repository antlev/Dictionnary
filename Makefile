CFLAGS = 
LFLAGS = -lm
#CFLAGS_DEBUG += -DDEBUG= -g
POSTFIX=
ifeq  ($(DEBUG),1)
	CFLAGS +=-DDEBUG=1 -g
	POSTFIX=_debug_1
else
ifeq ($(DEBUG),2)
	CFLAGS +=-DDEBUG=2 -g
	POSTFIX=_debug_2
else 
ifeq ($(DEBUG),3)
	CFLAGS +=-DDEBUG=3 -g
	POSTFIX=_debug_3
endif
endif
endif

#all: bin/main1 bin/main2

main1: bin/main1

#main2: bin/main2

bin/main1: src/gestrech.c src/gestorth.c src/utils.c src/gestbib.c src/main1.c
	gcc -o bin/main1${POSTFIX} src/gestrech.c src/gestorth.c src/utils.c src/gestbib.c src/main1.c $(CFLAGS) $(LFLAGS)

clean:
	rm -f bin/main1*