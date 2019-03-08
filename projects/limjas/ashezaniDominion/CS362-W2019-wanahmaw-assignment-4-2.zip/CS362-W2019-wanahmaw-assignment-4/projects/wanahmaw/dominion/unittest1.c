#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


//unit test 1 tests for initialize game starting with 10 curses, etsates, duchy, province
int main (int argc, char** argv) {
	struct gameState game;
    int kingdom[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
    initializeGame(2, kingdom, 3, &game);
    assert(game.supplyCount[curse] == 10);
    if (game.supplyCount[curse] == 10)
        printf("Test Successfully Complete\n");
    else
        printf("Test Failed\n");
    if (game.supplyCount[estate] == 8)
        printf("Test Successfully Complete\n");
    else
        printf("Test Failed\n");
    if (game.supplyCount[duchy] == 8)
        printf("Test Successfully Complete\n");
    else
        printf("Test Failed\n");
    if (game.supplyCount[province] == 8)
        printf("Test Successfully Complete\n");
    else
        printf("Test Failed\n");

    printf("\nFinished Unit Test 1: initialize game check different card sets\n");

	return 0;
}