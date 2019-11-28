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
	printf("unit test 1: Mine\n");
    srand(time(NULL));

    struct gameState state, test;
    int tests = 1,
    seed = 30,
    handPos = 1,
    currentPlayer = 0,
    nextPlayer = 1,
    numPlayers = 2,
    cardsInHands = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 minion, tribute, village, baron, adventurer};

    for (int i = 0; i < tests; i++)
    {
        printf("\n*** Begin Test %d / %d ***\n", i+1, tests);
        memset(&state, 23, sizeof(struct gameState));

        printf("initializeGame\n");
        initializeGame(numPlayers, k, seed, &state);

        state.handCount[currentPlayer] = cardsInHands;
        state.handCount[nextPlayer] = cardsInHands;
        state.hand[currentPlayer][handPos] = feast;
        
        // remove cards beyond the number of cardsInHands
        for (int j = cardsInHands; i <= state->handCount[5]; i++) {
            state->hand[currentPlayer][j] = -1;
        }
        state.hand[currentPlayer][handPos - 1] = copper;

        state.coins = 1;

        printHand(0, &state);

		printf("memcpy\n");
        memcpy(&test, &state, sizeof(struct gameState));

        // cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
        cardEffect(state.hand[currentPlayer][handPos], adventurer, 0, 0, &state, handPos, 0); // card we play; choice1, choice2, choice3 are related to the card we play: copper = 4, silver = 5; handPos = position of card we play; bonus is BS

        // discardCount should increment by only one, NOT two, since the card shouldn't be allowed to be purchased
        if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 1)) 
        {
            printf("Pass: discardCount Incremented by 1 and ONLY 1\n");
            
            // last card in discard pile should NOT be an adventurer
            if (state.discard[currentPlayer][state.discardCount[currentPlayer]] == adventurer)
            {
                printf("Fail: adventurer successfully purchased\n");
            }
            else
            {
                printf("Pass: adventurer NOT successfully purchased\n");
            }
        }
        else if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 2))
        {
            printf("Fail: discardCount Incremented by 2\n");

            // last card in discard pile should NOT be an adventurer
            if (state.discard[currentPlayer][state.discardCount[currentPlayer]] == adventurer)
            {
                printf("Fail: adventurer successfully purchased\n");
            }
            else
            {
                printf("Pass: adventurer NOT successfully purchased\n");
            }
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