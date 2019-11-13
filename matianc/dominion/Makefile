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

randomtest1: dominion.o rngs.o
	# First Random Test
	printf "***************** Rand Test 1 *****************\n\n" >> randomtestresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	printf "\n\nBaron GCOV Results:\n\n">> randomtestresults.out
	gcov -b -f dominion.c | grep playCardBaron -A 4 >> randomtestresults.out
	printf "\n************************************************\n\n\n" >> randomtestresults.out

randomtest2: dominion.o rngs.o
	# Second Random Test
	printf "***************** Rand Test 2 *****************\n\n" >> randomtestresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestresults.out
	printf "\n\nMinion GCOV Results:\n\n">> randomtestresults.out
	gcov -b -f dominion.c | grep playCardMinion -A 4 >> randomtestresults.out
	printf "\n************************************************\n\n\n" >> randomtestresults.out

randomtestresults: dominion.o rngs.o
	# First Random Test
	printf "***************** Rand Test 1 *****************\n\n" >> randomtestresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	printf "\n\nBaron GCOV Results:\n\n">> randomtestresults.out
	gcov -b -f dominion.c | grep playCardBaron -A 4 >> randomtestresults.out
	printf "\n************************************************\n\n\n" >> randomtestresults.out
	# Second Random Test
	printf "***************** Rand Test 2 *****************\n\n" >> randomtestresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestresults.out
	printf "\n\nMinion GCOV Results:\n\n">> randomtestresults.out
	gcov -b -f dominion.c | grep playCardMinion -A 4 >> randomtestresults.out
	printf "\n************************************************\n\n\n" >> randomtestresults.out
	# Third Random Test




player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe *.exe *.stackdump playdom player player.exe *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe *.out

