// Christopher Matian
// 11/5/2019 - OSU Fall Quarter 2019
// Unit Test 5 - Mine Card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <string.h>
// REFERENCE
// playCardMine(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer)
//      CHOICE 1 = INDEX OF CARD TO EXCHANGE
//      CHOICE 2 = ENUM VALUE OF CARD WE WANT TO EXCHANGE FOR
//      STATE = &G
//      HANDPOS = INDEX OF THE MINE CARD IN OUR HAND
//      CURRENTPLAYER = PLAYER

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

    printf("== Starting Unit Test for Mine Card ==\n");

    // Test One: Verify exception handling for out of bound choices for choice1
    // if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
    // {
    //     return -1;
    // }
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.testingCounter1 = 0;

    // Set player hand
    G.hand[player][0] = curse;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    // Pass curse card for choice1 - doesn't matter if the player has it or not for this test
    result = playCardMine(curse, silver, &G, 4, player);

    if (matian_assert(result == -1))
    {
        printf("\tTest %d Success - Exception handling caught OOB input for choice1: Result = %d\n", test, result);
    }
    else
    {
        printf("\tTest %d Failure - Exception handling failed to catch OOB input for choice1: Result = %d\n", test, result);
    }
    test++;

    // Test Two: Verify exception handling for out of bound choices for choice2
    // if (choice2 > treasure_map || choice2 < curse)
    // {
    //     return -2;
    // }
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    G.testingCounter1 = 0;
    // Set player hand
    G.hand[player][0] = curse;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    // Pass copper card idx for choice1 and -1 for choice 2.
    result = playCardMine(3, -1, &G, 4, player);

    if (matian_assert(result == -2))
    {
        printf("\tTest %d Success - Exception handling caught OOB input for choice2: Result = %d\n", test, result);
    }
    else
    {
        printf("\tTest %d Failure - Exception handling failed to catch OOB input for choice2: Result = %d\n", test, result);
    }
    test++;

    // Test Three: Verify exception handling for identical exchanges (trying to exchange copper for copper)
    // The function should ALLOW this behavior (see Mine card rules on treasure exchanges)
    // if ((getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2))
    // {
    //     return -3;
    // }
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    G.testingCounter1 = 0;
    // Set player hand
    G.hand[player][0] = curse;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    // Pass copper card for choice1 and copper for choice 2.
    result = playCardMine(1, copper, &G, 4, player);

    // It should allow this behavior which means we're looking for a result of 0 from the function return
    if (matian_assert(result == 0))
    {
        printf("\tTest %d Success - Exception handling - allowed the exchange of copper for copper: Result = %d\n", test, result);
    }
    else
    {
        printf("\tTest %d Failure - Exception handling failed - prevented exchange of copper for copper: Result = %d\n", test, result);
    }
    test++;

    // Test Four: Verify exception handling of copper for gold
    // if ((getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2))
    // {
    //     return -3;
    // }
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    G.testingCounter1 = 0; // reset testing counter (required)
    // Set player hand
    G.hand[player][0] = curse;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    // Pass copper card idx for choice1 and gold for choice 2.
    // The expected behavior is that the function will prevent the exchange
    result = playCardMine(1, gold, &G, 4, player);

    // If we don't hit the return function OR our counter has no value, then we know that the function failed to handle
    // this behavior correctly...
    if (matian_assert(result == -3 || G.testingCounter1 == 1))
    {
        printf("\tTest %d Success - Exception handling - can't exchange copper for gold: Result = %d, Counter = %d\n", test, result, G.testingCounter1);
    }
    else
    {
        printf("\tTest %d Failure - Exception handling failed - exchanged copper for gold: Result = %d, Counter = %d\n", test, result, G.testingCounter1);
    }
    test++;

    // Test Five: Verify that the player has only 1 silver card in their hand
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    G.testingCounter1 = 0; // reset testing counter

    // Set player hand
    G.hand[player][0] = copper;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = mine;
    G.hand[player][4] = copper;

    // Pass copper card idx for choice1 and silver for choice 2.
    result = playCardMine(4, silver, &G, 3, player);

    // count number of silver cards
    int silverCount = 0;
    for (int i = 0; i < G.handCount[player]; i++)
    {
        if (G.hand[player][i] == silver)
        {
            silverCount++;
        }
    }

    if (matian_assert(silverCount == 1))
    {
        printf("\tTest %d Success - player had correct number of silver cards at the end: Result = %d\n", test, silverCount);
    }
    else
    {
        printf("\tTest %d Failure - player had incorrect number of silver cards at the end: Result = %d\n", test, silverCount);
    }
    test++;

    // Test Six: Verify that only 1 copper card is trashed at the end of the function
    // We know for certain that when the mine card is played, there should be at least 3 copper cards in hand
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    G.testingCounter1 = 0; // reset testing counter

    // Set player hand
    G.hand[player][0] = copper;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    // Pass copper card idx for choice1 and silver for choice 2.
    result = playCardMine(0, silver, &G, 4, player);

    // count number of copper cards
    int copperCount = 0;
    for (int i = 0; i < G.handCount[player]; i++)
    {
        if (G.hand[player][i] == copper)
        {
            copperCount++;
        }
    }

    if (matian_assert(copperCount >= 3))
    {
        printf("\tTest %d Success - player had correct number of copper cards at the end: Result = %d\n", test, copperCount);
    }
    else
    {
        printf("\tTest %d Failure - player had incorrect number of copper cards at the end: Result = %d\n", test, copperCount);
    }
    test++;

    printf("== Ending Unit Test for Mine Card ==");
}