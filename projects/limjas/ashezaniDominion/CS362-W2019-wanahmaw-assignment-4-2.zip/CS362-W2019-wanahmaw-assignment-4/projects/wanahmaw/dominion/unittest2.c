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

//Unit test 2 test card buying function
int main (int argc, char** argv)	{
	struct gameState game;
	printf("\nUnit test 2: Buy Card \n");
	int testing = buyCard(2, &game);
	game.numBuys = 1;
	game.coins = 2;
	if(testing == -1)
		printf("Test Successfully Complete\n");
	else
		printf("Test Failed\n");

	printf("\nFinished Unit Test 2: Buy Card \n");

	return 0;
}