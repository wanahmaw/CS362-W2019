#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// This function tests whether adventurer correctly reveals cards from deck until 2 Treasure card are revealed and placed in hand by checking coin count in hand.

int main() {
	srand(time(NULL));
	
	printf("Testing adventurer card\n\n");
	
	int k[10] = {adventurer, village, remodel, great_hall, minion, steward, ambassador, embargo, outpost, sea_hag};
	
	int numPlayers2 = 2;
    int seed = 10000;
	int choice_1 = -1;
	int choice_2 = -1;
	int choice_3 = -1;
	int hand_position = -1;
	int* bonus_1 = 0;
	int whoseTurn = 0;
	int testPassed = 0;
	int testFailed = 0;
	
	

	// 100 random tests
	for(int i = 0; i < 100; i++) {
	printf("Test %d\n\n", i + 1);
	struct gameState *G = malloc(sizeof(struct gameState));
	initializeGame(numPlayers2, k, seed, G);
	int playerCardRand;
	int playerDeckRand = rand() % (MAX_DECK + 1);
	int playerHandRand = rand() % (playerDeckRand + 1);
	int playerKingdomCardRand;
	
	
		
	int beforeCoinsCount = 0;	
	int afterCoinsCount = 0;

	
	G->deckCount[0] = playerDeckRand - playerHandRand;
	G->handCount[0] = playerHandRand;
	
	G->deckCount[1] = playerDeckRand - playerHandRand;
	G->handCount[1] = playerHandRand;
	
	printf("deck + hand count: %d\n", playerDeckRand);
	printf("deck count: %d\n", G->deckCount[whoseTurn]);
	printf("hand count: %d\n", G->handCount[whoseTurn]);


	
	// randomize both player's deck
	 for (int i = 0; i < 2; i++){ //initialize random decks
		for (int j = 0; j < G->deckCount[i]; j++){
			playerCardRand = rand() % (17);
			playerKingdomCardRand = rand() % (10);
			if(playerCardRand == 0){
				G->deck[i][j] = copper;
			}
			else if(playerCardRand == 1){
				G->deck[i][j] = silver;
			}
			else if(playerCardRand == 2){
				G->deck[i][j] = gold;
			}
			else {
				G->deck[i][j] = k[playerKingdomCardRand];
			}
		}
	 }
	

	// count the number of coins in current player's hand
	for (int i = 0; i < G->handCount[whoseTurn]; i++){
        if (G->hand[whoseTurn][i] == copper || G->hand[whoseTurn][i] == silver || G->hand[whoseTurn][i] == gold){
           beforeCoinsCount++;
        }
    }
		
	printf("Player has %d coins before playing adventurer\n", beforeCoinsCount);
	
	// implement adventurer card effect
	cardEffect(adventurer, choice_1, choice_2, choice_3, G, hand_position, bonus_1);
	
	// count the number of coins in current player's hand after playing adventurer
	for (int j = 0; j < G->handCount[whoseTurn]; j++){
        if (G->hand[whoseTurn][j] == copper || G->hand[whoseTurn][j] == silver || G->hand[whoseTurn][j] == gold){
            afterCoinsCount++;
        }
    }
		
	
	
	if (afterCoinsCount == (beforeCoinsCount + 2)){
		printf("Passed. Player has %d coins\n\n", afterCoinsCount);
		testPassed = testPassed + 1;
	}
	else if (afterCoinsCount < beforeCoinsCount + 2){
		printf("Failed. too few coins. Player has %d coins\n\n", afterCoinsCount);
		testFailed = testFailed + 1;
	}
	else if (afterCoinsCount > beforeCoinsCount + 2){
		printf("Failed. too many coins. Player has %d coins\n\n", afterCoinsCount);
		testFailed = testFailed + 1;

	}
	
	
	free(G);
	


	}
	
	printf("%d tests passed\n", testPassed);
	printf("%d tests failed\n", testFailed);


	
	return 0;
}

