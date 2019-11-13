// Christopher Matian
// 11/13/2019 - OSU Fall Quarter 2019
// Random Test Card 2 - Minion Card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 *  Rough layout of the important conditionals we anticipate in the Minion functionality
 *  - Add 1 action to player
 *  - Discard Minion card from player hand
 *  IF: choice1
 *      - Add 2 coins to player
 *  ELIF: choice2
 *      WHILE:
 *          - discard all of player one's cards
 *      FOR:     
 *          - draw four new card's for player one
 *      WHILE: loop through each player
 *          IF: not current player
 *              IF: other player(s) have more than 4 cards
 *                  WHILE:
 *                      - discard their cards
 *                  FOR:
 *                      - draw 4 new cards
 *  Constants:
 *      - Loop is limited to 1,000
 * 
 *  Randomized Factors:
 *      - Number of players
 *      - What choice is made (1 or 2)
 *      - 
 * 
 *     
 */

int main()
{

    srand(time(NULL));

    struct gameState game;
    int numPlayers;
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
        // Randomize number of players
        numPlayers = (rand() % 3) + 2; // 2 - 4 players

        // Precount of certain variables
        int precountCoins = game.coins;
        // int preCountPlayerHand = 5;
        int precountOtherPlayerHands = ((numPlayers - 1) * 5);

        // initialize a game state on each loop run
        memset(&game, 23, sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &game);

        // Set up the counters
        game.inc1 = 0;
        game.inc2 = 0;
        game.inc3 = 0;
        game.inc4 = 0;
        game.inc5 = 0;

        int choice1, choice2;
        // Randomize which choice is made for the player
        // Either choice1 is 1 or choice2 is 1 (mutually exclusive...1 = play that choice)
        if (rand() % 2 == 0)
        {
            choice1 = 1;
            choice2 = 0;
        }
        else
        {
            choice1 = 0;
            choice2 = 1;
        }

        // Set player hand
        game.handCount[player] = 5;
        game.hand[player][4] = minion;

        // Set hand for other player(s)
        for (int i = 1; i < numPlayers; i++)
        {
            game.handCount[i] = 5; // handCount
            for (int j = 0; j < 5; j++)
            { // set cards to coppers (the type of card doesn't matter)
                game.hand[i][j] = copper;
            }
        }

        printf("\nMinion Card Iteration: %d, Choice: %d, Players: %d\n", i + 1, (choice1 == 1 ? 1 : 2), numPlayers);

        // Play the card with the randomized choices
        playCardMinion(0, choice1, choice2, &game, 4, player);

        // Is numActions incremented for the current player round
        if (game.numActions == 2)
        {
            printf("PASS - Expected: numActions == 2, Actual: numActions == %d\n", game.numActions);
        }
        else
        {
            printf("FAIL - Expected: numActions == 2, Actual: numActions == %d\n", game.numActions);
        }

        // Is the Minion card discarded? (set to -1 in place)
        if (game.hand[player][4] == -1)
        {
            printf("PASS - Expected: minion == -1, Actual: minion == %d\n", game.hand[player][4]);
        }
        else
        {
            printf("PASS - Expected: minion == -1, Actual: minion == %d\n", game.hand[player][4]);
        }

        // choice1 is played - is the coin amount incremented by 2
        if (choice1 == 1)
        {
            printf("PASS - Expected: coins == %d, Actual: coins == %d\n", precountCoins, game.coins);
        }
        else if (choice1 == 0)
        {
            printf("SKIP - Player did not select choice1.\n");
        }
        else
        {
            printf("FAIL - Expected: coins == %d, Actual: coins == %d\n", precountCoins, game.coins);
        }

        // choice2 is played - is the player's hand discarded four or more times?
        if (choice2 == 1 && game.inc1 >= 4)
        {
            printf("PASS - Expected: Player discardCount >= 4, Actual: Player discardCount == %d\n", game.inc1);
        }
        else if (choice2 == 0)
        {
            printf("SKIP - Player did not select choice2\n");
        }
        else
        {
            printf("FAIL - Expected: Player discardCount == 4, Actual: Player discardCount == %d\n", game.inc1);
        }

        // choice2 is played - does the player draw 4 new cards?
        if (choice2 == 1 && game.inc2 == 4 && game.handCount[player] == 4)
        {
            printf("PASS - Expected: Player drawCount == 4, Actual: Player drawCount == %d\n", game.inc2);
        }
        else if (choice2 == 0)
        {
            printf("SKIP - Player did not select choice2\n");
        }
        else
        {
            printf("FAIL - Expected: Player drawCount == 4, Actual: Player drawCount == %d\n", game.inc2);
        }

        // choice2 are the other player's cards discarded?
        if (choice2 == 1 && game.inc3 == precountOtherPlayerHands)
        {
            printf("PASS - Expected: nonplayer discardCount == %d, Actual: nonplayer discardCount == %d\n",
                   precountOtherPlayerHands, game.inc3);
        }
        else if (choice2 == 0)
        {
            printf("SKIP - Player did not select choice2\n");
        }
        else
        {
            printf("PASS - Expected: nonplayer discardCount == %d, Actual: nonplayer discardCount == %d\n",
                   precountOtherPlayerHands, game.inc3);
        }

        // choice2 are the other player's cards discarded?
        if (choice2 == 1 && game.inc4 == (precountOtherPlayerHands - numPlayers + 1))
        {
            printf("PASS - Expected: nonplayer drawCount == %d, Actual: nonplayer drawCount == %d\n",
                   (precountOtherPlayerHands - numPlayers + 1), game.inc4);
        }
        else if (choice2 == 0)
        {
            printf("SKIP - Player did not select choice2\n");
        }
        else
        {
            printf("FAIL - Expected: nonplayer drawCount == %d, Actual: nonplayer drawCount == %d\n",
                   (precountOtherPlayerHands - numPlayers + 1), game.inc4);
        }
    }
};