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

unittestresults:
	printf "*****************  Unit Test 1 *****************\n\n" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	printf "\n\nGCOV Results:\n\n">> unittestresults.out
	gcov -b -f dominion.c | grep playCardBaron -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out 

	printf "*****************  Unit Test 2 *****************\n\n" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	printf "\n\nGCOV Results:\n\n">> unittestresults.out
	gcov -b -f dominion.c | grep playCardMinion -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

	printf "*****************  Unit Test 3 *****************\n\n" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	printf "\n\nGCOV Results:\n\n">> unittestresults.out
	gcov -b -f dominion.c | grep playCardAmbassador -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

	printf "*****************  Unit Test 4 *****************\n\n" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	printf "\n\nGCOV Results:\n\n">> unittestresults.out
	gcov -b -f dominion.c | grep playCardTribute -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out     

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe *.exe *.stackdump playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
