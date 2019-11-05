// Christopher Matian
// 11/4/2019 - OSU Fall Quarter 2019
// Unit Test 1 - Baron Card

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
    int supply;
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

    printf("== Starting Unit Test for Baron Card ==\n");

    // Test One: verify that numBuys for player is increased when card is played
    // Set up player's hand (0 - 4)
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Set player hand to have the baron card
    G.hand[player][4] = baron;
    // Play the baron card
    playCardBaron(1, 0, &G, 4, player);

    if ((result = matian_assert(G.numBuys == 2))) // numBuys should be 2
    {
        printf("\t- Test %d Success - numBuys is incremented: numBuys = %d\n", test, G.numBuys);
    }
    else
    {
        printf("\t- Test %d Failure - numBuys is not incremented: numBuys = %d\n", test, G.numBuys);
    }
    test++;

    // Test Two: verify that the coins for state are incremented by 4
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Set player hand to test estate if conditional
    G.hand[player][0] = estate;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;

    // Play the baron card
    G.coins = 0;
    playCardBaron(1, 1, &G, 4, player);

    if ((result = matian_assert(G.coins == 4)))
    {
        printf("\t- Test %d Success - Coins are incremented: Coins = %d\n", test, G.coins);
    }
    else
    {
        printf("\t- Test %d Failure - Coins are not incremented: Coins = %d\n", test, G.coins);
    }
    test++;

    // Test Three: verify that handCount for player is decremented when they hold an estate card
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Set player hand to test estate if conditional
    G.hand[player][0] = estate;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;

    // Play the baron card
    playCardBaron(1, 1, &G, 4, player);

    if ((result = matian_assert(G.handCount[player] == 4))) // Result should be 4 because the player has 5 cards
    {
        printf("\t- Test %d Success - Handcount is decremented: Handcount = %d\n", test, G.handCount[player]);
    }
    else
    {
        printf("\t- Test %d Failure - Handcount is not decremented: Handcount = %d\n", test, G.handCount[player]);
    }
    test++;

    // Test Four: verify that the estate supplyCount from the else-if clause is decremented properly (only once)
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Set player hand to ELIF conditional because they don't have an estate card in hand
    G.hand[player][0] = mine;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;
    // Get supply count of estates before execution
    supply = G.supplyCount[estate];
    // Play the baron card
    playCardBaron(1, 1, &G, 4, player);

    // Result should be less than original estate supply count by 1. We compare it like this because in theory a supplyCount
    // of 27 + 1 will equal to the original supply count value of 28. If its decremented more than once then the evaluation will fail.
    if ((result = matian_assert(G.supplyCount[estate] + 1 == supply)))
    {
        printf("\t- Test %d Success - supplyCount is decremented only once: supplyCount: %d < Original: %d\n", test, G.supplyCount[estate], supply);
    }
    else
    {
        printf("\t- Test %d Failure - SupplyCount is decremented more than once: supplyCount: %d < Original: %d\n", test, G.supplyCount[estate], supply);
    }
    test++;

    // Test Five: verify that the estate supplyCount from the ELSE (very bottom of the function) clause is decremented properly (only once)
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Set player hand to ELIF conditional because they don't have an estate card in hand
    G.hand[player][0] = mine;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;
    // Get supply count of estates before execution
    supply = G.supplyCount[estate];
    // Play the baron card
    playCardBaron(1, 0, &G, 4, player);

    // Result should be less than original estate supply count by 1. We compare it like this because in theory a supplyCount
    // of 27 + 1 will equal to the original supply count value of 28. If its decremented more than once then the evaluation will fail.
    if ((result = matian_assert(G.supplyCount[estate] + 1 == supply)))
    {
        printf("\t- Test %d Success - supplyCount is decremented only once: supplyCount: %d < Original: %d\n", test, G.supplyCount[estate], supply);
    }
    else
    {
        printf("\t- Test %d Failure - SupplyCount is decremented more than once: supplyCount: %d < Original: %d\n", test, G.supplyCount[estate], supply);
    }

    printf("== Ending Unit Test for Baron Card ==");
}
