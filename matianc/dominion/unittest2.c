// Christopher Matian
// 11/4/2019 - OSU Fall Quarter 2019
// Unit Test 2 - Minion Card

/** Notes
 * 
 * - The bug that prevented the second player's hand from being discarded had to be fixed otherwise it 
 *   would prevent 100% code coverage.
 * - Tracing counters had to be added to state for ease of incrementing. The purpose is to track while loops
 *   that discard or gain card's for any given player.
 * 
 * 
 * */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <string.h>

// Custom Assert Function for result testing
int matian_assert(int eval)
{
    // If test case is false return false (0)
    // Exit early for better (albeit insignificant) performance when errors are hit
    if (!eval)
    {
        return 0;
    }
    // else return true (1)
    return 1;
};

int main()
{
    int numPlayers = 2;
    int seed = 30;
    int player = 0;
    int result;
    int coins;
    int test = 1;

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

    printf("== Starting Unit Test for Minion Card ==\n");

    // Test One: verify for either choice actions are incremented once for the player
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;
    playCardMinion(0, 0, &G, player, 4);

    if ((result = matian_assert(G.numActions == 2)))
    {
        printf("\tTest %d Success - numActions is incremented: numAction = %d\n", test, G.numActions);
    }
    else
    {
        printf("\tTest %d Failure - numActions is not incremented: numAction = %d\n", test, G.numActions);
    }
    test++;

    // Test Two: verify for choice 1 that coins are incremented by 2
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;
    coins = G.coins;

    playCardMinion(1, 0, &G, player, 4);

    if ((result = matian_assert(G.coins == coins + 2)))
    {
        printf("\tTest %d Success - coins are incremented by 2: coins = %d, oldcoins = %d\n", test, G.coins, coins);
    }
    else
    {
        printf("\tTest %d Failure - coins are not incremented by 2: coins = %d oldcoins = %d\n", test, G.coins, coins);
    }
    test++;

    // Test Three: verify for either choice that the minion card is discarded
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;

    playCardMinion(1, 0, &G, player, 4);

    if ((result = matian_assert(G.hand[player][4] == -1)))
    {
        printf("\tTest %d Success - player's minion card is discarded: Value = %d\n", test, G.hand[player][4]); // expect -1
    }
    else
    {
        printf("\tTest %d Failure - player's minion card is not discarded: Value = %d\n", test, G.hand[player][4]);
    }
    test++;

    // Test Four: verify for choice 2 that the player's cards are discarded no more than 4 times within the while loop
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;
    G.inc1 = 0;

    playCardMinion(0, 1, &G, player, 4);

    if ((result = matian_assert(G.inc1 > 0 && G.inc1 <= 4)))
    {
        printf("\tTest %d Success - player's hand is discarded no more than 4 times: Total = %d\n", test, G.inc1);
    }
    else
    {
        printf("\tTest %d Failure - player's hand is discarded more than 4 times: Total = %d\n", test, G.inc1);
    }
    test++;

    // Test Five: verify for choice 2 that the enemy's cards are discarded 5 times (or more)
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    // Forcefully set up player two's hand
    G.hand[1][0] = mine;
    G.hand[1][1] = mine;
    G.hand[1][2] = mine;
    G.hand[1][3] = mine;
    G.hand[1][4] = mine;
    G.handCount[1] = 5; // Set his handCount manually

    G.hand[player][4] = minion;
    G.inc2 = 0;

    playCardMinion(0, 1, &G, player, 4);

    // If the counter is 0 it means that the other player's cards were not discarded.
    // We expect that since this is the first turn, effectively the other number of players will have to discard
    // up to 15 cards total (2 players = 1 * 5, 3 players = 2 * 5, 4 players = 3 * 5)
    if ((result = matian_assert(G.inc2 > 0 && G.inc2 <= (numPlayers - 1) * 5)))
    {
        printf("\tTest %d Success - Enemy's hand is discarded correctly (0 > n <= (numPlayers - 1) * 5): Total = %d\n", test, G.inc2);
    }
    else
    {
        printf("\tTest %d Failure - Enemy's hand is not discarded correctly (0 > n <= (numPlayers - 1) * 5): Total = %d\n", test, G.inc2);
    }
    test++;

    // Test Six: verify for choice 2 that the player draws only 4 cards
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Forcefully set up player two's hand
    G.hand[1][0] = mine;
    G.hand[1][1] = mine;
    G.hand[1][2] = mine;
    G.hand[1][3] = mine;
    G.hand[1][4] = mine;
    G.handCount[1] = 5; // Set his handCount manually

    G.hand[player][4] = minion; // Set player one's hand to have a minion card for playing
    int handCount = G.handCount[player];

    playCardMinion(0, 1, &G, player, 4);

    if ((result = matian_assert(G.handCount[player] < handCount)))
    {
        printf("\tTest %d Success - Player only drew 4 cards: Total = %d\n", test, G.handCount[player]);
    }
    else
    {
        printf("\tTest %d Failure - Player drew more than 4 cards: Total = %d\n", test, G.handCount[player]);
    }
    test++;

    printf("== Ending Unit Test for Minion Card ==");
}