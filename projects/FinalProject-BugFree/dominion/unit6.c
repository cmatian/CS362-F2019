#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <assert.h>
#include "rngs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	printf("unit test 1: Feast\n");
    srand(time(NULL));

    struct gameState state, test;
    int currentPlayer = state.whoseTurn;
    int nextPlayer = currentPlayer + 1;
    int tests = 1,
    seed = 30,
    handPos = 4,
    numPlayers = 2,
    cardsInHands = 7;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 minion, tribute, village, baron, province};

        // printf("\n*** Begin Test %d / %d ***\n", 1, tests);
        memset(&state, 23, sizeof(struct gameState));

        // printf("initializeGame\n");
				state.handCount[currentPlayer] = cardsInHands;
				state.handCount[nextPlayer] = cardsInHands;

        initializeGame(numPlayers, k, seed, &state);
				int card = feast;
				int choice1Card = adventurer;
        int choice1Index = 1;
        int choice2Index = 2;
        int choice3Index = 3;

        state.handCount[currentPlayer] = cardsInHands;
        state.handCount[nextPlayer] = cardsInHands;
        state.hand[currentPlayer][6] = card;
				state.hand[currentPlayer][4] = copper;
				state.hand[currentPlayer][5] = copper;

				// printf("attempting to add this card to discard pile: %d\n\n", state.hand[currentPlayer][4]);
        //state.hand[currentPlayer][choice1Index] = choice1Card;
        // unnecessary to remove cards beyond the number of cardsInHands and any other set cards
        // for (int j = cardsInHands; j < cardsInHands - 1; j++) {
        //     state.hand[currentPlayer][j] = -1;
        // }

        //state.coins = 2;
				updateCoins(currentPlayer, &state, 0);
				// printf("Coins: %d \n", state.coins);
				// printf("state.handCount[currentPlayer]: %d\n", state.handCount[currentPlayer]);
        // printHand(0, &state);
				// printDiscard(0, &state);

		// printf("memcpy\n");
        memcpy(&test, &state, sizeof(struct gameState));

            if (supplyCount(choice1Card, &state) <= 0) {
                    printf("None of that card left, sorry!\n");
                    printf("Cards Left: %d\n", supplyCount(choice1Card, &state));
            }
            // else if (state.coins < getCost(choice1Card)) {
            //     printf("That card is too expensive!\n");
            //         printf("Coins: %d < %d\n", state.coins, getCost(choice1Card));
            // }
            else if (5 >= getCost(choice1Card)) {
                printf("That card is affordable!\n");
                printf("Coins: %d >= %d\n", state.coins, getCost(choice1Card));
            }

        // cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
        cardEffect(card, choice1Card, 0, 0, &state, handPos, 0); // card we play; choice1, choice2, choice3 are related to the card we play: copper = 4, silver = 5; handPos = position of card we play; bonus is BS
				//
				// printf("state.playedCardCount: %d\n", state.playedCardCount);
				// printf("state.playedCards[state.playedCardCount - 1]: %d\n", state.playedCards[state.playedCardCount - 1]); // choice2 that you trash
				// printf("state.playedCards[state.playedCardCount - 2]: %d\n", state.playedCards[state.playedCardCount - 2]); // treasure card that you play
				//
				// printf("state.handCount[currentPlayer]: %d\n", state.handCount[currentPlayer]);
				// printf("state.deckCount[currentPlayer]: %d\n", state.deckCount[currentPlayer]);
				// printf("state.discardCount[currentPlayer]: %d\n", state.discardCount[currentPlayer]);
				// printf("state.hand[currentPlayer][0]: %d\n", state.hand[currentPlayer][0]);
				printPlayed(0, &state);
				printDiscard(0, &state);
				printHand(0, &state);

        // discardCount should increment by only one, NOT two, since the card shouldn't be allowed to be purchased
        if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 1) && state.discard[currentPlayer][state.discardCount[currentPlayer] - 1] == choice1Card)
        {
            printf("Fail: adventurer successfully purchased\n");
        }
        else
        {
            printf("Pass: adventurer NOT successfully purchased\n");
        }

        // 	else if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 2))
        // {
        //     printf("Fail: discardCount Incremented by 2\n");
				//
        //     // last card in discard pile should NOT be an adventurer
        //     if (state.discard[currentPlayer][state.discardCount[currentPlayer]] == choice1Card)
        //     {
        //         printf("Fail: adventurer successfully purchased\n");
        //     }
        //     else
        //     {
        //         printf("Pass: adventurer NOT successfully purchased\n");
        //     }
        // }
        // else
        // {
        //     printf("Fail: discardCount NOT Incremented by 1 and ONLY 1\n");
        // }

        // handCount should decrement, but not really that relevant to this test case
        // if (state.handCount[currentPlayer] == (test.handCount[currentPlayer] - 1))
        // {
        //     printf("Pass: handCount Decremented\n");
        // }
        // else
        // {
        //     printf("Fail: handCount NOT Decremented\n");
        // }

				//printHand(0, &state);
				// printDiscard(0, &state);

    return 0;
}
