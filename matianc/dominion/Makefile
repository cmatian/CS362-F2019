CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresults:
	# First Random Test
	printf "*****************  Rand Test 1 *****************\n\n" >> randomtestresults.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	printf "\n\nGCOV Results:\n\n">> randomtestresults.out
	gcov -b -f dominion.c | grep playCardBaron -A 4 >> randomtestresults.out
	printf "\n************************************************\n\n\n" >> randomtestresults.out

	# Second Random Test

	# Third Random Test




player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe *.exe *.stackdump playdom player player.exe *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe *.out

