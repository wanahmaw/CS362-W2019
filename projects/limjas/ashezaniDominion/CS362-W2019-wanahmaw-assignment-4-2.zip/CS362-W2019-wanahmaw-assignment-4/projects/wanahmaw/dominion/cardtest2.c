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

//smithy card to test drawing
int main()
{
    struct gameState game;
    int kingdom[10] = {adventurer, feast, gardens, village, remodel, mine, cutpurse, baron, tribute, smithy};
    int myCard = adventurer;
    int myChoice1 = -1;
    int myChoice2 = -1;
    int myChoice3 = -1;
    int myHandPos = -1;
    int* myBonus = 0;
    initializeGame(2, kingdom, 500, &game);
    printf("Card Test 2: Smithy\n");
    game.handCount[game.whoseTurn] = 1; //set handcount to 1 for testing
    int i = game.handCount[game.whoseTurn];
    cardEffect(myCard, myChoice1, myChoice2, myChoice3, &game, myHandPos, myBonus);
    int j = i+2;
    if(j == game.handCount[game.whoseTurn])
    {
        printf("Smithy passed all test successfully\n");
    }
    else
    {
        printf("\nTest Failed\n");
    }

    printf("Finished Card Test 2: Smithy\n");

    return 0;
}