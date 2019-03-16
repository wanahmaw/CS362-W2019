/*
 * unittest1.c
 * 
 * Include the following lines in your makefile:
 * unittest.1: unittest.1.c dominion.o rngs.o
 *      gcc -o unittest.1 -g unittest.1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define FUNCTEST "isGameOver()"

int ERRORS = 0; //global error count

void assertTrue (int a, int b)
{
    if (a != b)
    {
        printf("assert failed\n");
        ERRORS++;
    }
}

int main() {
    int i, j, r, expected;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;

    initializeGame(numPlayers, k, seed, &G);    //create new game

    printf("TESTING %s:\n", FUNCTEST);

    //check function works with provinces
    for (i = -1; i < 2; i++)
    {
        printf("Test with %d provinces\n", i);
        memcpy(&testG, &G, sizeof(struct gameState));   //copy game state to test case
        testG.supplyCount[province] = i;                //set province supply count
        r = isGameOver(&testG);

        //expected isGameOver result for province supply count
        if (i == 0)
            expected = 1;
        else
            expected = 0;
        
        printf("isGameOver = %d, expected = %d\n", r, expected);
        assertTrue(r, expected);   //check if game over with valid province supply count

        //check if supply count changed for any CARDS by comparing with G state
        for (j = 0; j <= treasure_map; j++)
        {
            if (j == province)
            {
                printf("CARD[%d] supply count = %d, expected = %d\n", j, testG.supplyCount[j], i);
                assertTrue(testG.supplyCount[j], i);    //we changed province count before isGameOver()
            }
            else  
            {
                printf("CARD[%d] supply count = %d, expected = %d\n", j, testG.supplyCount[j], 
                G.supplyCount[j]);
                assertTrue(testG.supplyCount[j], G.supplyCount[j]);
            }
        }
    }

    //check function works with empty suppy piles
    for (i = 0; i < 4; i++)
    {
        printf("Test with %d empty supply piles\n", i);
        memcpy(&testG, &G, sizeof(struct gameState));   //copy game state to test case

        //set supply count to 0
        for (j = 0; j < i; j++)
            testG.supplyCount[j] = 0;

        r = isGameOver(&testG);

        //expected isGameOver result for empty supply count
        if (i == 3)
            expected = 1;
        else
            expected = 0;

        printf("isGameOver = %d, expected = %d\n", r, expected);
        assertTrue(r, expected);    //check if game over with valid empty supply count

        //check if supply count changed for any CARDS by comparing with G state
        //we don't check supply counts we changed
        for (j = i; j <= treasure_map; j++)
        {
                printf("CARD[%d] supply count = %d, expected = %d\n", j, testG.supplyCount[j], 
                G.supplyCount[j]);
                assertTrue(testG.supplyCount[j], G.supplyCount[j]);
        }
    }

    //print test result
    if (ERRORS == 0)
        printf("All tests passed!\n");
    else
        printf("Tests failed %d times\n", ERRORS);
    
    return 0;
}
