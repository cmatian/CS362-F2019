// BUG 7 UNIT TESTS

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
    int player2 = 1;

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

    printf("== Starting Unit Test for Tribute Card - Bug 7 ==\n");

    // Test One: Check duplicate action handling
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    // Set Hand for Player 1
    // Player starts with a total of 5 coins
    G.handCount[player1] = 5;
    G.hand[player1][0] = copper;
    G.hand[player1][1] = copper;
    G.hand[player1][2] = copper;
    G.hand[player1][3] = copper;
    G.hand[player1][4] = tribute;

    // Set discard counts, deck counts, and hand for player2
    G.discardCount[player2] = 0;
    G.deckCount[player2] = 10;
    G.deck[player2][7] = village;
    G.hand[player2][8] = village;
    G.hand[player2][9] = village;

    cardEffect(tribute, 0, 0, 0, &G, 4, 0);

    // Actions should only be 3
    if (G.numActions == 3)
    {
        printf("PASS - Expected: Actions == 3\tActual: Actions == %d\n", G.numActions);
    }
    else
    {
        printf("FAIL - Expected: Actions == 3\tActual: Actions == %d\n", G.numActions);
    }

    printf("== End of Unit Test for Tribute Card - Bug 7 ==\n");
}