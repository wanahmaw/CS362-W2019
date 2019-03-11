#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// This function tests whether playing council room increases buys by 1
int main() {

	srand(time(NULL));
	printf("Testing council room card\n");
	
	int k[10] = {council_room, village, remodel, great_hall, minion
			   , steward, ambassador, embargo, outpost, sea_hag};
	struct gameState G;
	int numPlayers2 = 2;
    int seed = 10000;
	int choice_1 = -1;
	int choice_2 = -1;
	int choice_3 = -1;
	int *bonus = 0;
	int whoseTurn;
	int testPassed = 0;
	int testFailed = 0;

	
	// 100 random tests
	for(int i = 0; i < 100; i++) {
	printf("Test %d\n\n", i + 1);
	initializeGame(numPlayers2, k, seed, &G);
	
	whoseTurn = G.whoseTurn;

	
	G.phase = 0;
	if (G.numActions < 1) {
		G.numActions = 1;
	}
	

	G.hand[whoseTurn][0] = council_room;
	int randBuys = rand() % (100 + 1);
	int buysBeforePlayingCard;

	buysBeforePlayingCard = randBuys;
	G.numBuys = buysBeforePlayingCard;

	printf("Testing with %d buy(s) before playing card\n", G.numBuys);

	
	// play council room card
	cardEffect(council_room, choice_1, choice_2, choice_3, &G, 0, bonus);
	
	
	if (G.numBuys == buysBeforePlayingCard + 1) {
		// after playing council room card, buys should increase by one
		printf("Test passed.  Played council room, number of buys updated to %d successfully\n\n", buysBeforePlayingCard + 1);
		testPassed++;
	}
	else if (G.numBuys > buysBeforePlayingCard + 1) {
		printf("Test failed. number of buys updated to %d and is too many buys\n\n", G.numBuys);
		testFailed++;
	}
	else {
		printf("Test failed. number of buys updated to %d and is too few buys\n\n", G.numBuys);
		testFailed++;
	}
	
	}
	
	printf("%d tests passed\n", testPassed);
	printf("%d tests failed\n", testFailed);


	return 0;
}