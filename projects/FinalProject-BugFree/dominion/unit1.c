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
  printf("unit test 1: Mine\n");
  srand(time(NULL));

  struct gameState state, test;
  int seed = 30,
      handPos = 4,
      currentPlayer = 0,
      nextPlayer = 1,
      numPlayers = 2,
      cardsInHands = 5;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
               minion, tribute, village, baron, great_hall};

  // printf("\n*** Begin Test %d / %d ***\n", 1, tests);
  memset(&state, 23, sizeof(struct gameState));

  // printf("initializeGame\n");
  initializeGame(numPlayers, k, seed, &state);

  int card = mine;
  int choice1 = copper;
  int choice2 = silver;
  int choice3 = 0;

  state.handCount[currentPlayer] = cardsInHands;
  state.handCount[nextPlayer] = cardsInHands;
  state.hand[currentPlayer][choice1] = choice1;
  state.hand[currentPlayer][choice2] = choice2;

  // printHand(0, &state);

  // printf("memcpy\n");
  memcpy(&test, &state, sizeof(struct gameState));

  // cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
  cardEffect(card, choice1, choice2, choice3, &state, handPos, 0); // card we play; choice1, choice2, choice3 are related to the card we play: copper = 4, silver = 5; handPos = position of card we play; bonus is BS

  // printf("state.playedCardCount: %d\n", state.playedCardCount);
  // printf("state.playedCards[state.playedCardCount - 1]: %d\n", state.playedCards[state.playedCardCount - 1]); // choice2 that you trash
  // printf("state.playedCards[state.playedCardCount - 2]: %d\n", state.playedCards[state.playedCardCount - 2]); // treasure card that you play
  //
  // printf("state.handCount[currentPlayer]: %d\n", state.handCount[currentPlayer]);
  // printf("state.discardCount[currentPlayer]: %d\n", state.discardCount[currentPlayer]);
  // printf("state.hand[currentPlayer][0]: %d\n", state.hand[currentPlayer][0]);

  // playedCardCount should increment by only 1 since the choice1 card should be trashed, not discarded
  if (state.playedCardCount == (test.playedCardCount + 1))
  {
    printf("\n Pass: only 1 card added to played card count \n\n");
  }
  else
  {
    printf("\n Fail: card added to playedCard Pile \n");
  }

  // if want to see if gain the card you wanted to:
  // && state.hand[currentPlayer][0] == choice2

  // handCount should increment by 1

  //discardCount should stay the same

  // deckCount should decrement, but mine and discard don't do that, only gaincard does, so not relevant for this bug

  // supplyCount should decrement, but mine and discard don't do that, only gaincard does, so not relevant for this bug

  // printHand(0, &state);

  return 0;
}
