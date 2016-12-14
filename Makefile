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

ifeq  ($(LETTER_SET),1)
	CFLAGS +=-DSET_OF_LETTERS_ACCEPTED=1
else
ifeq ($(LETTER_SET),2)
	CFLAGS +=-DSET_OF_LETTERS_ACCEPTED=2
else 
ifeq ($(LETTER_SET),3)
	CFLAGS +=-DSET_OF_LETTERS_ACCEPTED=3
else
ifeq ($(LETTER_SET),4)
	CFLAGS +=-DSET_OF_LETTERS_ACCEPTED=4
endif
endif
endif
endif

all: bin/main1 bin/main2 bin/main3 bin/main4

main1: bin/main1

main2: bin/main2

main3: bin/main3

main4: bin/main4

bin/main1: src/main1.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c
	gcc -o bin/main1${POSTFIX} src/main1.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c $(CFLAGS) $(LFLAGS)

bin/main2: src/main2.c src/gestrech.c src/utils.c
	gcc -o bin/main2${POSTFIX} src/main2.c src/gestrech.c src/utils.c $(CFLAGS) $(LFLAGS)

bin/main3: src/main3.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c
	gcc -o bin/main3${POSTFIX} src/main3.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c $(CFLAGS) $(LFLAGS)

bin/main4: src/main4.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c
	gcc -o bin/main4${POSTFIX} src/main4.c src/gestbib.c src/gestrech.c src/gestorth.c src/utils.c $(CFLAGS) $(LFLAGS)

clean:
	rm -f bin/main*