#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


// This function tests whether village correctly draws a card and adds it to the player's hand
int main() {

	
	printf("Testing village card\n");
	
	int k[10] = {smithy, village, remodel, great_hall, minion, steward, ambassador, embargo, outpost, sea_hag};
	int numPlayers2 = 2;
    int seed = 10000;
	int choice_1 = -1;
	int choice_2 = -1;
	int choice_3 = -1;
	int hand_position = 0;
	int *bonus_1 = 0;
	int whoseTurn = 0;
	int testPassed = 0;
	int testFailed = 0;

	
	// 100 random tests
	for(int i = 0; i < 100; i++) {
	printf("Test %d\n\n", i + 1);
	struct gameState *G = malloc(sizeof(struct gameState));
	initializeGame(numPlayers2, k, seed, G);

	
	whoseTurn = G->whoseTurn;

	
	G->phase = 0;
	if (G->numActions < 1) {
		G->numActions = 1;
	}
	
	// set players' deck and hand count
	int playerDeckRand = rand() % (MAX_DECK + 1);
	int playerHandRand = rand() % (playerDeckRand + 1);
	
	int handBeforePlayingCard = playerHandRand;
	
	G->deckCount[0] = playerDeckRand - playerHandRand;
	G->handCount[0] = playerHandRand;
	
	G->deckCount[1] = playerDeckRand - playerHandRand;
	G->handCount[1] = playerHandRand;
		
	printf("Before playing village, player has %d cards in hand\n\n", G->handCount[whoseTurn]);

	// play village
	cardEffect(village, choice_1, choice_2, choice_3, G, hand_position, bonus_1);
	
	
	if (G->handCount[whoseTurn] == handBeforePlayingCard) {
		// after playing the card, hand count should stay the same as before as we gained 1 card and discarded village
		printf("Test passed.  Played village, added 1 card to hand, discarded village from hand, and set player's hand to %d successfully\n\n", playerHandRand);
		testPassed++;
	}
	else if (G->handCount[whoseTurn] > handBeforePlayingCard) {
		printf("Test failed, player's hand has %d cards in it after playing village and is too many cards\n\n", G->handCount[whoseTurn]);
		testFailed++;
	}
	else {
		printf("Test failed, player's hand has %d cards in it after playing village annd is too few cards\n\n", G->handCount[whoseTurn]);
		testFailed++;
	}
	

	free(G);
	

	}

	printf("%d tests passed\n", testPassed);
	printf("%d tests failed\n", testFailed);
	
	return 0;
}