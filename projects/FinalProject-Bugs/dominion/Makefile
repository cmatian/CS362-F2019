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


unit7:
	printf "*****************  Unit Test 7 *****************\n\n" >> unittestresult_7.out
	gcc -o unit7 unit7.c -g dominion.c rngs.c $(CFLAGS)
	./unit7 >> unittestresult_7.out
	printf "\n\nGCOV Results:\n">> unittestresult_7.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresult_7.out
	printf "\n************************************************\n\n\n" >> unittestresult_7.out

unit9:
	printf "*****************  Unit Test 9 *****************\n\n" >> unittestresult_9.out
	gcc -o unit9 unit9.c -g dominion.c rngs.c $(CFLAGS)
	./unit9 >> unittestresult_9.out
	printf "\n\nGCOV Results:\n">> unittestresult_9.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresult_9.out
	printf "\n************************************************\n\n\n" >> unittestresult_9.out

unit10:
	printf "*****************  Unit Test 10 *****************\n\n" >> unittestresult_10.out
	gcc -o unit10 unit10.c -g dominion.c rngs.c $(CFLAGS)
	./unit10 >> unittestresult_10.out
	printf "\n\nGCOV Results:\n">> unittestresult_10.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresult_10.out
	printf "\n************************************************\n\n\n" >> unittestresult_10.out

unit11:
	printf "*****************  Unit Test 11 *****************\n\n" >> unittestresult_11.out
	gcc -o unit11 unit11.c -g dominion.c rngs.c $(CFLAGS)
	./unit11 >> unittestresult_11.out
	printf "\n\nGCOV Results:\n">> unittestresult_11.out
	gcov -b -f dominion.c | grep cardEffect -A 4 >> unittestresult_11.out
	printf "\n************************************************\n\n\n" >> unittestresult_11.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe *.exe
