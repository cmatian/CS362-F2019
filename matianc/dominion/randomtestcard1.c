// Christopher Matian
// 11/11/2019 - OSU Fall Quarter 2019
// Random Test Card 1 - Baron Card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdlib.h>
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
 *      - loop is limited to 1,000 iterations max (initially) - why:
 *          - I am a human being with a finite amount of time on this planet.
 *          - I have a CS 372 FTP project that I want to work on as well :-)
 *          - I will scale the number and mention the recommended iter value in the documentation. I'm looking 
 *            to just hit 90% or more branch coverage.
 *      - Player always starts with 5 cards in their hand
 *      - Player always has a Baron card in their hand (this is a given)
 * 
 *  Randomized Factors:
 *      - whether the player has an estate card in their hand
 *      - what choice the player decides to make (0 or 1)
 *      - the number of estate cards in the supply
 */

int main()
{

    srand(time(NULL));

    struct gameState game;
    int numPlayers = 2;
    int seed = 30;
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
    int limit = 1000; // Limit loop

    for (int i = 0; i < limit; i++) // Run the card test up to 10,000 times
    {
        // initialize a game state on each loop run
        memset(&game, 23, sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &game);
        game.handCount[player] = 5; // Player should always have 5 cards in hand each draw

        int precountEstate = game.supplyCount[estate];

        // Randomize the choice
        int choice = (rand() % 2); // 0 or 1

        // Set whether the fourth card in the player's hand is an estate or a copper
        // If 0 - estate
        // If 1 - copper
        game.hand[player][3] = (rand() % 2) == 0 ? estate : copper;

        // Set the player's baron card
        game.hand[player][4] = baron; // Last card in player's hand is always a baron card

        // Print out the Deck Size and the current iteration
        printf("\nBaron Card Iteration: %d, Choice: %d, Card 3: %s\n", i + 1, choice,
               (game.hand[player][3] == estate ? "estate" : "copper"));
        playCardBaron(0, choice, &game, 4, player); // Play the Baron Card

        // Print Statements
        // First IF - Numbuys is incremented to 2
        if (game.numBuys == 2)
        {
            printf("PASS - Expected: numBuys == 2, Actual: numBuys == %d\n", game.numBuys);
        }
        else
        {
            printf("FAIL - Expected: numBuys == 2, Actual: numBuys == %d\n", game.numBuys);
        }

        // Player opted for choice 1 and possessed an estate card
        if (choice == 1 && game.handCount[player] == 4)
        {
            printf("PASS - Expected: Handcount == 4, Actual: Handcount == %d\n", game.handCount[player]);
        }
        else if (choice == 0 || game.hand[player][3] == copper)
        {
            printf("SKIP - Did not evaluate for player possessing an estate card.\n");
        }
        else
        {
            printf("FAIL - Expected: Handcount == 4, Actual: Handcount == %d\n", game.handCount[player]);
        }

        // Player opted for choice 1 but did not possess an estate card
        // Estate count from supply should be decremented once
        if (choice == 1 && game.supplyCount[estate] == precountEstate - 1)
        {
            printf("PASS - Expected: supplyCount[estate] == %d, Actual: supplyCount[estate] == %d\n", precountEstate - 1, game.supplyCount[estate]);
        }
        else if (choice == 0 || (choice == 1 && game.handCount[player] == 4))
        {
            printf("SKIP - Did not evaluate supplyCount ELIF conditional\n");
        }
        else
        {
            printf("FAIL - Expected: supplyCount[estate] == %d, Actual: supplyCount[estate] == %d\n", precountEstate - 1, game.supplyCount[estate]);
        }
    }
};
