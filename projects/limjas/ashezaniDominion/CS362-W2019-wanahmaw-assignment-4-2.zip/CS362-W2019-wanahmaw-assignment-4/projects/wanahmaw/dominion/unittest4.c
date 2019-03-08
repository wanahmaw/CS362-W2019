#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

//test to check how many cards in hand unit test 4
int main (int argc, char** argv)	{
	struct gameState game;
	int kingdom[10] = {adventurer, feast, gardens, village, remodel, mine, cutpurse, baron, tribute, smithy};
	int i;
	printf ("\nUnit Test 4: Num of cards in hand\n");
	initializeGame(2, kingdom, 3, &game);
	i = numHandCards(&game);
	assert(i == *game.handCount);
	printf("Test Successfully Complete\n");

	printf("\nFinished Unit Test 4: Num cards in hand\n");

	return 0;
}