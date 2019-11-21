CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

unit2: dominion.o unit2.c
	gcc -o unit2 unit2.c -g dominion.o rngs.o $(CFLAGS)

unit3: dominion.o unit3.c
	gcc -o unit3 unit3.c -g dominion.o rngs.o $(CFLAGS)

unit4: dominion.o unit4.c
	gcc -o unit4 unit4.c -g dominion.o rngs.o $(CFLAGS)

unit5: dominion.o unit5.c
	gcc -o unit5 unit5.c -g dominion.o rngs.o $(CFLAGS)

clean:
	rm -f *.o unit2.exe unit2 unit3.exe unit3 unit4.exe unit4 unit5.exe unit5 player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
