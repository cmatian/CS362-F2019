// Christopher Matian
// 11/14/2019 - OSU Fall Quarter 2019
// Random Test Card 3 - Tribute Card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 *  Layout of the important conditionals we anticipate in the Tribute function
 * 
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
    int player2 = 1;
    int k[27] = {
        curse,
        estate,   // victory
        duchy,    // victory
        province, // victory
        copper,   // treasure
        silver,   // treasure
        gold,     // treasure
        adventurer,
        council_room,
        feast,
        gardens, // victory
        mine,
        remodel,
        smithy,
        village,
        baron,
        great_hall, // victory
        minion,
        steward,
        tribute,
        ambassador,
        cutpurse,
        embargo,
        outpost,
        salvager,
        sea_hag,
        treasure_map};
    int kc[10] = {
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

    for (int i = 0; i < limit; i++) // Run the card test up to 1,000 times
    {
        // Just two players needed for this test
        numPlayers = 2;

        // initialize a game state on each loop run
        memset(&game, 23, sizeof(struct gameState));
        initializeGame(numPlayers, kc, seed, &game);

        // Tribute Revealed Cards
        int tributeRevealedCards[2] = {-1, -1};

        // Precount of certain variables
        int precountCoins = game.coins;
        // int precountBuys = game.numBuys;
        int precountAction = game.numActions;
        // int precountOtherPlayerHands = ((numPlayers - 1) * 5);

        // Set up the counters
        game.inc1 = 0;
        game.inc2 = 0;
        game.inc3 = 0;
        game.inc4 = 0;
        game.inc5 = 0;

        game.handCount[player] = 5;
        game.handCount[player2] = 5;

        // Generate random cards for player 1's hand (only the first 4)
        for (int i = 0; i < 4; i++)
        {
            int randCard = rand() % 27;
            game.hand[player][i] = k[randCard];
        }
        game.hand[player][4] = tribute;

        // Generate 5 random cards for player 2's hand
        for (int i = 0; i < 5; i++)
        {
            int randCard = rand() % 27;
            game.hand[player][i] = k[randCard];
        }

        // Generate random cards for player 2's deck
        for (int i = 0; i < game.deckCount[player2]; i++)
        {
            int randCard = rand() % 27;
            game.deck[player2][i] = randCard;
        }

        // Log player 1's handCount before the function executes
        int precountPlayerHandCount = game.handCount[player];

        // Log player 2's top 2 cards - these are the cards the function will draw from
        int precountTopCard1 = game.deck[player2][game.deckCount[player2] - 1];
        int precountTopCard2 = game.deck[player2][game.deckCount[player2] - 2];

        // printf("Discard Count Player 1: %d\n", game.discardCount[player]);
        // printf("Deck Count Player 1: %d\n", game.deckCount[player]);

        // printf("Discard Count Player 2: %d\n", game.discardCount[player2]);
        // printf("Deck Count Player 2: %d\n", game.deckCount[player2]);

        // printf("Player 2's Deck Top Card: %d, Just Below: %d, Just Below 2: %d\n", game.deck[player2][game.deckCount[player2] - 1],
        //        game.deck[player2][game.deckCount[player2] - 2], game.deck[player2][game.deckCount[player2] - 3]);

        playCardTribute(0, tributeRevealedCards, &game, player, player2);

        // printf("Tribute Array: %d, %d\n", tributeRevealedCards[0], tributeRevealedCards[1]);
        // printf("Player 1 Handcount: %d\n", game.handCount[player]);
        // printf("Coins Before: %d, After: %d\n", precountCoins, game.coins);
        // printf("Actions: %d\n", game.numActions);
        // printf("Buys: %d\n", game.numBuys);

        int actionsTaken = 0;
        // Were coins changed?
        if (game.coins > precountCoins)
        {
            actionsTaken++;
        }
        // Were 2 cards drawn for player 1?
        if (game.handCount[player] > precountPlayerHandCount)
        {
            actionsTaken++;
        }
        // Were actions changed?
        if (game.numActions > precountAction)
        {
            actionsTaken++;
            // This if-block means that the for-loop ran a second or third time (in the tribute function)
            if (game.numActions - precountAction == 4)
            {
                actionsTaken += 1;
            }

            if (game.numActions - precountAction == 6)
            {
                actionsTaken += 2;
            }
        }

        // actionsTaken referred to the actions of the tribute card, not the player's actions
        printf("\nTribute Card Iteration: %d, Actions: %d, Players: %d\n", i + 1, actionsTaken, numPlayers);

        // Were all three possible actions taken? Add 2 coins, 2 cards, and 2 actions?
        // Remember - only up to 2 actions can possibly occur...
        if (actionsTaken <= 2)
        {
            printf("PASS - Expected: actionsTaken <= 2, Actual: actionsTaken == %d\n", actionsTaken);
        }
        else
        {
            printf("FAIL - Expected: actionsTaken <= 2, Actual: actionsTaken == %d\n", actionsTaken);
        }

        // Is the curse card causing actions to get incremented?
        if (
            (tributeRevealedCards[0] == curse || tributeRevealedCards[1] == curse) &&
            (game.numActions >= 2))
        {
            printf("FAIL - Expected: numActions with curse card <= 2, Actual: numActions == %d\n", game.numActions);
        }
        else if ((tributeRevealedCards[0] != curse && tributeRevealedCards[1] != curse))
        {
            printf("SKIP - Curse card not in the tributeRevealedCards array.\n");
        }
        else
        {
            printf("PASS - Expected: numActions with curse card <= 2, Actual: numActions == %d\n", game.numActions);
        }

        // Are the top 2 cards correctly being played?
        if (tributeRevealedCards[0] == (precountTopCard1) &&
            tributeRevealedCards[1] == (precountTopCard2))
        {
            printf("PASS - Expected: DeckTopCard1 == %d && DeckTopCard2 == %d\n\t\tActual: DeckTopCard1 == % d && DeckTopCard2 == % d\n ", precountTopCard1, precountTopCard2, tributeRevealedCards[0], tributeRevealedCards[1]);
        }
        else
        {
            printf("FAIL - Expected: DeckTopCard1 == %d && DeckTopCard2 == %d\n\t\tActual: DeckTopCard1 == % d && DeckTopCard2 == % d\n ", precountTopCard1, precountTopCard2, tributeRevealedCards[0], tributeRevealedCards[1]);
        }
    }
};