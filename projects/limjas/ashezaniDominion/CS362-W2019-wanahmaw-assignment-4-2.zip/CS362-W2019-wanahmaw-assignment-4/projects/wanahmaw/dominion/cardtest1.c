/*
 * Jason Lim
 * CS 362
 * 2/10/19
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//adventure card test count the coinsCountures
int main()
{
	struct gameState game, testgame;
    int coinsCount = 0;
	int i = 0;
    int coinsCount1 = 0;
    int coinsCount2 = 0;
    int maxHand[MAX_HAND];
    int kingdom[10] = {adventurer, feast, gardens, village, remodel, mine, cutpurse, baron, tribute, smithy};
	int myCard = adventurer;
	int myChoice1 = -1;
	int myChoice2 = -1;
	int myChoice3 = -1;
	int myHandPos = -1;
	int* myBonus = 0;
	initializeGame(2, kingdom, 500, &game);
    memcpy(&testgame, &game, sizeof(struct gameState));
    printf("Card Test 1: Adventurer\n");
    game.handCount[game.whoseTurn] = 1; //set handcount to 1 for testing
	cardEffect(myCard, myChoice1, myChoice2, myChoice3, &game, myHandPos, myBonus);
    while(coinsCount<2){
        drawCard(game.whoseTurn, &game);
        int drawHand = game.hand[game.whoseTurn][game.handCount[game.whoseTurn]-1];
        if (drawHand == copper || drawHand == silver || drawHand == gold){
            coinsCount++;
        }
        else{
            maxHand[i]=drawHand;
            game.handCount[game.whoseTurn]--;
            i++;
        }
    }
    for(int i = 0; i < game.handCount[game.whoseTurn]; i++){
        if (game.hand[game.whoseTurn][i] == copper || game.hand[game.whoseTurn][i] == silver || game.hand[game.whoseTurn][i] == gold){
            coinsCount1++;
        }
    }
    for(int i = 0; i < testgame.handCount[testgame.whoseTurn]; i++){
        if (testgame.hand[testgame.whoseTurn][i] == copper || testgame.hand[testgame.whoseTurn][i] == silver || testgame.hand[testgame.whoseTurn][i] == gold){
            coinsCount2++;
        }
    }
	if(coinsCount1 == coinsCount2)
	{
		printf("Adventurer passed all test successfully\n");
	}
	else
	{
		printf("\nTest Failed\n");
	}

	printf("Finished Card Test 1: Adventurer\n");

	return 0;
}