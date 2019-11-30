// BUG 10 UNIT TESTS

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    int numPlayers = 2;
    int seed = 30;
    int player1 = 0;

    // Card Set-up
    int k[10] = {
        adventurer,
        ambassador,
        embargo,
        village,
        minion,
        mine,
        cutpurse,
        baron,
        tribute,
        smithy};

    // Game State
    struct gameState G;

    printf("== Starting Unit Test for Ambassador Card - Bug 10 ==\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    // Set Hand for Player 1
    // Player starts with a total of 5 coins
    G.handCount[player1] = 5;
    G.hand[player1][0] = copper;
    G.hand[player1][1] = copper;
    G.hand[player1][2] = gold;
    G.hand[player1][3] = gold;
    G.hand[player1][4] = ambassador;

    int result = cardEffect(ambassador, 3, 2, 0, &G, 4, 0);

    if (result == 0)
    {
        printf("PASS - Expected: Return Code 0\tActual: Return Code %d\n", result);
    }
    else
    {
        printf("FAIL - Expected: Return Code 0\tActual: Return Code %d\n", result);
    }

    printf("== End of Unit Test for Ambassador Card - Bug 10 ==\n");
}