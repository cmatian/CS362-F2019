// Christopher Matian
// 11/11/2019 - OSU Fall Quarter 2019
// Random Test Card 1 - Baron Card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 *  Rough layout of the important conditionals we anticipate in the Baron functionality
 *      START
 *      - numBuys is incremented
 *      - IF: player wants to discard their estate card (choice1 > 0)
 *          - IF: player has an estate card in hand:
 *              - handCount of player is decremented
 * 
 *          - ELIF: player doesn't have an estate card in hand:
 *              - state->supplyCount[estate] is decremented
 * 
 *      -  ELSE: player gains an estate card instead
 *      END
 * 
 *  Constants:
 *      - numPlayers, seed, starting player and potential cards
 *      - loop is limited to 10,000 iterations max - why:
 *          - I am a human being with a finite amount of time on this planet.
 *      - Player always starts with 5 cards in their hand
 *      - Player always has a Baron card in their hand (this is a given)
 * 
 *  Randomized Factors:
 *      - whether the player has an estate card in their hand
 *      - what choice the player decides to make (0 or 1)
 *      - the number of estate cards in the supply
 */

void runTest()
{
}

int main()
{

    srand(time(NULL));

    struct gameState game;
    int numPlayers = 2;
    int seed = 30;
    int randomDraw;
    int maxDeck;
    int deckSize = 25;
    int player = 0;
    int k[10] = {
        adventurer,
        ambassador,
        baron,
        minion,
        tribute,
        village,
        mine,
        cutpurse,
        smithy,
        embargo};
    int limit = 10000; // Limit loop

    for (int i = 0; i < limit; i++) // Run the card test up to 10,000 times
    {
        // initialize a game state on each loop run
        initializeGame(numPlayers, k, seed, &game);
        game.handCount[player] = 5; // Player should always have 5 cards in hand each draw

        // Print out the Deck Size and the current iteration
        printf("Iteration: %d\n", i + 1);

        testBaronCard();
    }
};
