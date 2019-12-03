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
    handPos = 4,
    currentPlayer = 0,
    nextPlayer = 1,
    numPlayers = 2,
    cardsInHands = 5;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 minion, tribute, village, baron, great_hall};

    for (int i = 0; i < tests; i++)
    {
        printf("\n*** Begin Test %d / %d ***\n", i+1, tests);
        memset(&state, 23, sizeof(struct gameState));

        printf("initializeGame\n");
        initializeGame(numPlayers, k, seed, &state);

        int card = mine;
        int choice1Index = 1;
        int choice2Index = 2;
        int choice3Index = 3;
        
        state.handCount[currentPlayer] = cardsInHands;
        state.handCount[nextPlayer] = cardsInHands;
        state.hand[currentPlayer][choice1Index] = copper;
        state.hand[currentPlayer][choice2Index] = silver; 

        printHand(0, &state);

		printf("memcpy\n");
        memcpy(&test, &state, sizeof(struct gameState));
        
        // cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
        cardEffect(card, choice1Index, choice2Index, choice3Index, &state, handPos, 0); // card we play; choice1, choice2, choice3 are related to the card we play: copper = 4, silver = 5; handPos = position of card we play; bonus is BS

        // playedCardCount should increment by only 1 since the choice1 card should be trashed, not discarded
        if (state.playedCardCount == (test.playedCardCount + 1)) 
        {
            printf("Pass: playedCardCount Incremented\n");
        }
        else
        {
            printf("Fail: playedCardCount NOT Incremented\n");
        }

        // handCount should stay the same since replacing, but not really that relevant to this test case
        // if (state.handCount[currentPlayer] == test.handCount[currentPlayer])
        // {
        //     printf("Pass: handCount Unchanged\n");
        // }
        // else
        // {
        //     printf("Fail: handCount NOT Unchanged\n");
        // }


        // discardCount should increment by only 1 since the choice1 card should be trashed, not discarded, but mine and discard don't do that, so not relevant for this bug
        // if (state.discardCount[currentPlayer] == (test.discardCount[currentPlayer] + 1)) 
        // {
        //     printf("Pass: discardCount Unchanged\n");
        // }
        // else
        // {
        //     printf("Fail: discardCount NOT Unchanged\n");
        // }

        // deckCount should decrement, but mine and discard don't do that, only gaincard does, so not relevant for this bug

        // supplyCount should decrement, but mine and discard don't do that, only gaincard does, so not relevant for this bug

        printHand(0, &state);
    }

    return 0;
}
