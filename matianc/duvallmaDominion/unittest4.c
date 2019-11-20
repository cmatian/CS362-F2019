// Christopher Matian
// 11/4/2019 - OSU Fall Quarter 2019
// Unit Test 4 - Tribute Card

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
    int player1 = 0;
    int player2 = 1;
    int test = 1;
    int tributeRevealed[2] = {-1, -1};

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

    printf("== Starting Unit Test for Tribute Card ==\n");

    // Test One: Verify first if-conditional for when the nextPlayer's deckCount is decremented
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    // Set Hand for Player 1
    G.hand[player1][4] = tribute;

    // Set Hand for Player 2
    G.discardCount[player2] = 0;
    G.deckCount[player2] = 1;

    playCardTribute(0, tributeRevealed, &G, player1, player2);

    // The deck count should be decremented by 1
    if (matian_assert(G.deckCount[player2] == 0))
    {
        printf("\tTest %d Success - Deck count for player 2 was decremented: Deck Count = %d\n", test, G.deckCount[player2]);
    }
    else
    {
        printf("\tTest %d Failure - Deck count for player 2 was not decremented: Deck Count = %d\n", test, G.deckCount[player2]);
    }
    test++;

    // Test Two: Verify that the ELIF conditional for decrementing the discardCount of nextPlayer
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Reset tributeRevealed
    tributeRevealed[0] = -1;
    tributeRevealed[1] = -1;

    // Set Hand for Player 1
    G.hand[player1][4] = tribute;

    // Set Hand for Player 2
    G.discardCount[player2] = 1;
    G.deckCount[player2] = 0;

    playCardTribute(0, tributeRevealed, &G, player1, player2);

    if (matian_assert(G.discardCount[player2] == 0))
    {
        printf("\tTest %d Success - Deck count for player 2 was decremented: Discard Count = %d\n", test, G.discardCount[player2]);
    }
    else
    {
        printf("\tTest %d Failure - Deck count for player 2 was not decremented: Discard Count = %d\n", test, G.discardCount[player2]);
    }
    test++;

    // Test Three: Verify the number of coins that are incremented
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Reset tributeRevealed
    tributeRevealed[0] = copper;
    tributeRevealed[1] = copper;

    int numCoins = G.coins;

    // Set Hand for Player 1
    G.hand[player1][4] = tribute;

    // Set Hand for Player 2
    G.discardCount[player2] = 2;
    G.deckCount[player2] = 2;

    playCardTribute(0, tributeRevealed, &G, player1, player2);

    // Should only add 2 coins at first
    if (matian_assert(G.coins == numCoins + 2))
    {
        printf("\tTest %d Success - Total coins were incremented by 2 only: Total Coins = %d\n", test, G.coins);
    }
    else
    {
        printf("\tTest %d Failure - Total coins are incremented by more than 2: Total Coins = %d\n", test, G.coins);
    }
    test++;

    printf("== Ending Unit Test for Ambassador Card ==");
}