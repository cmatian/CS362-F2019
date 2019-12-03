CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

unit1:
	printf "*****************  Unit Test 1 *****************\n\n" >> unittestresults.out
	gcc -o unit1 unit1.c -g dominion.c rngs.c interface.c $(CFLAGS)
	./unit1 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit2:
	printf "*****************  Unit Test 2 *****************\n\n" >> unittestresults.out
	gcc -o unit2 unit2.c -g dominion.c rngs.c $(CFLAGS)
	./unit2 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit3:
	printf "*****************  Unit Test 3 *****************\n\n" >> unittestresults.out
	gcc -o unit3 unit3.c -g dominion.c rngs.c $(CFLAGS)
	./unit3 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit4:
	printf "*****************  Unit Test 4 *****************\n\n" >> unittestresults.out
	gcc -o unit4 unit4.c -g dominion.c rngs.c $(CFLAGS)
	./unit4 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit5:
	printf "*****************  Unit Test 5 *****************\n\n" >> unittestresults.out
	gcc -o unit5 unit5.c -g dominion.c rngs.c $(CFLAGS)
	./unit5 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit6:
	printf "*****************  Unit Test 6 *****************\n\n" >> unittestresults.out
	gcc -o unit6 unit6.c -g dominion.c rngs.c interface.c $(CFLAGS)
	./unit6 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit7:
	printf "*****************  Unit Test 7 *****************\n\n" >> unittestresults.out
	gcc -o unit7 unit7.c -g dominion.c rngs.c $(CFLAGS)
	./unit7 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit9:
	printf "*****************  Unit Test 9 *****************\n\n" >> unittestresults.out
	gcc -o unit9 unit9.c -g dominion.c rngs.c $(CFLAGS)
	./unit9 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit10:
	printf "*****************  Unit Test 10 *****************\n\n" >> unittestresults.out
	gcc -o unit10 unit10.c -g dominion.c rngs.c $(CFLAGS)
	./unit10 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unit11:
	printf "*****************  Unit Test 11 *****************\n\n" >> unittestresults.out
	gcc -o unit11 unit11.c -g dominion.c rngs.c $(CFLAGS)
	./unit11 >> unittestresults.out
	printf "\n\nGCOV Results:\n">> unittestresults.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresults.out
	printf "\n************************************************\n\n\n" >> unittestresults.out

unittestresults: unit1 unit2 unit3 unit4 unit5 unit6 unit7 unit9 unit10 unit11

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe *.exe unit1 unit2 unit3 unit4 unit5 unit6 unit7 unit9 unit10 unit11