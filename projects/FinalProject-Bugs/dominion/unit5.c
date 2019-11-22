/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include<time.h> 
#include "rngs.h"




// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assertion(int input, int expected);
int main() {

    int seed = 1000;
    int k[10] = {estate, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    G.coins = 0;

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);

    printf ("TESTING Bug 5:\n");
    int player = 0;

    G.hand[player][0] = estate;
    G.hand[player][1] = estate;
    G.handCount[player] = 2;

    G.discard[player][0] = estate;
    G.discard[player][1] = estate;
    G.discardCount[player] = 2;

    G.deck[player][0] = estate;
    G.deck[player][1] = estate;
    G.deck[player][2] = estate;
    G.deckCount[player] = 3;

    int expected = 7;

    int value = scoreFor(0, &G);  
    assertion(value, expected);
    return 0;
}

void assertion(int input, int expected)
{
    printf("Returned Value: %d\n", input);
    printf("Expected Value: %d\n", expected);
    if(input != expected)
    {
        printf("TEST FAILED\n");
    }

    else
    {
        printf("TEST PASSED\n");
    }
}


