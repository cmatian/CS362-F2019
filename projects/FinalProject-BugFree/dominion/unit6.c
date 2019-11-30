#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <assert.h>
#include "rngs.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	printf("unit test 1: Adventurer\n");
    srand(time(NULL));

    struct gameState state, test;
    int currentPlayer = state.whoseTurn;
    int nextPlayer = currentPlayer + 1;
    int tests = 1,
    seed = 30,
    handPos = 4,
    numPlayers = 2,
    cardsInHands = 5;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 minion, tribute, village, baron, province};

    for (int i = 0; i < tests; i++)
    {
        printf("\n*** Begin Test %d / %d ***\n", i+1, tests);
        memset(&state, 23, sizeof(struct gameState));

        printf("initializeGame\n");
        initializeGame(numPlayers, k, seed, &state);

        state.handCount[currentPlayer] = cardsInHands;
        state.handCount[nextPlayer] = cardsInHands;
        state.hand[currentPlayer][handPos] = feast;
        state.hand[currentPlayer][handPos - 1] = copper;
        // unnecessary to remove cards beyond the number of cardsInHands and any other set cards
        // for (int j = cardsInHands; j < cardsInHands - 1; j++) {
        //     state.hand[currentPlayer][j] = -1;
        // }

        state.coins = 1;

        printHand(0, &state);

		printf("memcpy\n");
        memcpy(&test, &state, sizeof(struct gameState));

            int choice1 = adventurer;
            if (supplyCount(choice1, &state) <= 0) {
                    printf("None of that card left, sorry!\n");
                    printf("Cards Left: %d\n", supplyCount(choice1, &state));
            }
            else if (state.coins < getCost(choice1)) {
                printf("That card is too expensive!\n");
                    printf("Coins: %d < %d\n", state.coins, getCost(choice1));
            }
            else if (state.coins >= getCost(choice1)) {
                printf("That card is affordable!\n");
                    printf("Coins: %d >= %d\n", state.coins, getCost(choice1));
            }

        // cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
        cardEffect(state.hand[currentPlayer][handPos], choice1, 0, 0, &state, handPos, 0); // card we play; choice1, choice2, choice3 are related to the card we play: copper = 4, silver = 5; handPos = position of card we play; bonus is BS

        // discardCount should increment by only one, NOT two, since the card shouldn't be allowed to be purchased
        if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 1)) 
        {
            printf("Pass: discardCount Incremented by 1 and ONLY 1\n");
            
        //     // last card in discard pile should NOT be an adventurer
        //     if (state.discard[currentPlayer][state.discardCount[currentPlayer]] == adventurer)
        //     {
        //         printf("Fail: adventurer successfully purchased\n");
        //     }
        //     else
        //     {
        //         printf("Pass: adventurer NOT successfully purchased\n");
        //     }
        // }
        // else if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 2))
        // {
        //     printf("Fail: discardCount Incremented by 2\n");

        //     // last card in discard pile should NOT be an adventurer
        //     if (state.discard[currentPlayer][state.discardCount[currentPlayer]] == adventurer)
        //     {
        //         printf("Fail: adventurer successfully purchased\n");
        //     }
        //     else
        //     {
        //         printf("Pass: adventurer NOT successfully purchased\n");
        //     }
        }
        else
        {
            printf("Fail: discardCount NOT Incremented by 1 and ONLY 1\n");
        }

        // handCount should decrement, but not really that relevant to this test case
        // if (state.handCount[currentPlayer] == (test.handCount[currentPlayer] - 1))
        // {
        //     printf("Pass: handCount Decremented\n");
        // }
        // else
        // {
        //     printf("Fail: handCount NOT Decremented\n");
        // }

        printHand(0, &state);
    }

    return 0;
}