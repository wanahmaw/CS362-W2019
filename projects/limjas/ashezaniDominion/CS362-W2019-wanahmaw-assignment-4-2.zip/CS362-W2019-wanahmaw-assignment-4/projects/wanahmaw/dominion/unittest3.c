/*
 * Jason Lim
 * CS 362
 * 2/10/19
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// tests if finished with turn unit test 3
int main(int argc, char** argv)
{
	struct gameState game;
	int kingdom[10] = {adventurer, feast, gardens, village, remodel, mine, cutpurse, baron, tribute, smithy};
	int i = initializeGame(2, kingdom, 5, &game);

	printf("\nUnit Test 3: Check turn over \n");
	int j = 0;
	j = isGameOver(&game);
	assert(j == 0);
	printf("\nTest Successfully Complete\n");

	printf("\nFinished Unit Test 3: Is the turn over? \n");

	assert(i == 0);
	return 0;
} 