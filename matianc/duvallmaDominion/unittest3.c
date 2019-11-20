// Christopher Matian
// 11/4/2019 - OSU Fall Quarter 2019
// Unit Test 3 - Ambassador Card

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

    printf("== Starting Unit Test for Ambassador Card ==\n");

    // Test One: Verify that the if-conditional for out of bound choice2 is correctly caught and handled
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][3] = curse;
    G.hand[player][3] = curse;      // Set up 2 curse cards
    G.hand[player][4] = ambassador; // Set player one's hand to have a ambassador card for playing

    result = playCardAmbassador(0, 3, 4, &G, player); // Pass a result for choice2 that is out of bounds

    // We altered the ambassador function slightly to provide different error codes so that we can achieve better coverage and
    // determine where errors occurred in the negative return cases.
    // If the result is -1 it means that the result was validated correctly.
    if (matian_assert(result == -1))
    {
        printf("\tTest %d Success - Correctly validated the player's choice2 argument: Function Return = %d\n", test, result);
    }
    else
    {
        printf("\tTest %d Failure - Incorrectly validated the player's choice2 argument: Function Return = %d\n", test, result);
    }
    test++;

    // Test Two: Verify that the if-conditional for choice1 is correctly caught and handled
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][3] = curse;      // Set up curse cards
    G.hand[player][4] = ambassador; // Set player one's hand to have a ambassador card for playing

    result = playCardAmbassador(4, 2, 4, &G, player); // Pass a result for choice1 that is equal to the handPos

    // If the result is -2 it means that the result was validated correctly.
    if (matian_assert(result == -2))
    {
        printf("\tTest %d Success - Correctly validated the player's choice1 argument: Function Return = %d\n", test, result);
    }
    else
    {
        printf("\tTest %d Failure - Incorrectly validated the player's choice1 argument: Function Return = %d\n", test, result);
    }
    test++;

    // Test Three: Verify for situations where the user tries to discard more copies than they actually have
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][3] = curse;      // Set up 1 curse cards
    G.hand[player][4] = ambassador; // Set player one's hand to have a ambassador card for playing

    // Pass a result for choice1 and try to discard more than there are cards
    result = playCardAmbassador(3, 2, 4, &G, player); // Pass a result for choice1 and try to discard more than there are cards

    // If the result is -3 it means that the result was validated correctly and prevented us from discarding more than the actual number of cards in the player's hand.
    if (matian_assert(result == -3))
    {
        printf("\tTest %d Success - player cannot try to discard more than exists of that card in hand: Function Return = %d\n", test, result);
    }
    else
    {
        printf("\tTest %d Failure - player was able to discard more than exists of that card in hand: Function Return = %d\n", test, result);
    }
    test++;

    // Test Four: Validate that the other player receives a copy of the card that's discarded from hand
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][3] = curse;      // Set up 1 curse cards
    G.hand[player][4] = ambassador; // Set player one's hand to have a ambassador card for playing

    int discardCount = G.discardCount[1];
    playCardAmbassador(3, 1, 4, &G, player);

    if (matian_assert(G.discardCount[1] > discardCount))
    {
        printf("\tTest %d Success - Enemy player gained a copy of the card: Discard Count = %d\n", test, G.discardCount[1]);
    }
    else
    {
        printf("\tTest %d Failure - Enemy player did not gain a copy of the card: Discard Count = %d\n", test, G.discardCount[1]);
    }
    test++;

    printf("== Ending Unit Test for Ambassador Card ==");
}