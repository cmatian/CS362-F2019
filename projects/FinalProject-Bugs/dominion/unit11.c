// BUG 11 UNIT TEST

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

    printf("== Starting Unit Test for Minion Card - Bug 11 ==\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    // Set Hand for Player 1
    // Player starts with a total of 5 coins
    G.handCount[player1] = 5;
    G.hand[player1][0] = copper;
    G.hand[player1][1] = copper;
    G.hand[player1][2] = gold;
    G.hand[player1][3] = gold;
    G.hand[player1][4] = minion;

    int precountCoins = G.coins;

    // Pass all 0's for choice1 and choice2
    // This will cause a card to be discarded and the player will gain an action.
    // Assume the player wanted choice1 (gain 2 coins)
    cardEffect(minion, 0, 0, 0, &G, 4, 0);

    if (G.handCount[player1] == 4 && G.numActions == 2 && G.coins == precountCoins + 2)
    {
        printf("PASS - Expected: coins == %d\tActual: Coins == %d\n", precountCoins + 2, G.coins);
    }
    else
    {
        printf("FAIL - Expected: coins == %d\tActual: Coins == %d\n", precountCoins + 2, G.coins);
    }

    printf("== End of Unit Test for Minion Card - Bug 11 ==\n");
}