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

//council test, testing num buys
int main()
{
    struct gameState game;
    int kingdom[10] = {adventurer, feast, council_room, village, remodel, mine, cutpurse, baron, tribute, smithy};
    int myCard = council_room;
    int myChoice1 = -1;
    int myChoice2 = -1;
    int myChoice3 = -1;
    int myHandPos = -1;
    int* myBonus = 0;
    initializeGame(2, kingdom, 500, &game);
    printf("Card Test 4: Council\n");
    game.numBuys = 1; //set numBuys to 1 for testing
    int i = game.numBuys;
    cardEffect(myCard, myChoice1, myChoice2, myChoice3, &game, myHandPos, myBonus);
    int j = i+1;
    printf("manualtest#buys: %d\n", j);
    printf("numbuys: %d", game.numBuys);
    if(j == game.numBuys)
    {
        printf("Council passed all test successfully\n");
    }
    else
    {
        printf("\nTest Failed\n");
    }

    printf("Finished Card Test 4: Council\n");

    return 0;
}
