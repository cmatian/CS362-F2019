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

void assertion(int input);
int main() {
    //int i;
    int seed = 1000;
    //int numPlayer = 2;
    //int maxBonus = 10;
    //int p, r, handCount;
    //int bonus;
    int k[10] = {estate, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    G.coins = 0;
    //int maxHandCount = 10;
    // arrays of all coppers, silvers, and golds
    //int coppers[MAX_HAND];
    //int silvers[MAX_HAND];
    //int golds[MAX_HAND];
    /*for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }*/

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);

    printf ("TESTING Bug 3:\n");
    //provence costs 8 in index 3
    //curse costs 0 in index 0

    //12 for remodel
    //0 for choice1 
    //1 for choice2
    //choice3 is not important, so 0
    //G for gamestate
    //handPos is not important, so 0
    //Bonus is not important, so 0
    int card = remodel;
    int choice1 = 0;
    int choice2 = 3;
    int choice3 = 0;
    int handPos = 0;


    //G.playedCards[100];
    G.playedCardCount = 0;
    //G.hand[0][choice1];


    int value = cardEffect(card, choice1, choice2, choice3, &G, handPos, 0);  
    assertion(value);
    return 0;
}

void assertion(int input)
{
    printf("Returned Value: %d\n", input);
    printf("Expected Value: -1\n");
    if(input == 0)
    {
        printf("TEST FAILED\n");
    }

    else
    {
        printf("TEST PASSED\n");
    }
}

