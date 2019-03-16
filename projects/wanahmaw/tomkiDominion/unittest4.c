/*
 * unittest4.c
 * 
 * Include the following lines in your makefile:
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define FUNCTEST "getCost()"

int ERRORS = 0; //global error count

void assertTrue (int a, int b, int equal)
{
    if (equal && a == b)
    {
        printf("assert failed\n");
        ERRORS++;
    }
    else if (!equal && a != b)
    {
        printf("assert failed\n");
        ERRORS++;
    }

}

int main() {
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    int cost[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 
                3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    int card[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer,
                    council_room, feast, gardens, mine, remodel, smithy, village,
                    baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
                    embargo, outpost, salvager, sea_hag, treasure_map};
    struct gameState G, testG;
    int maxHandCount = 5;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game for comparison

    printf("TESTING %s:\n", FUNCTEST);

    //check cost of each card
    for (i = 0; i < 27; i++)
    {
        printf("getCost(%d) = %d, expected = %d\n", card[i], getCost(card[i]), cost[i]);
        assertTrue(getCost(card[i]), cost[i], 0);
    }

    //loop over 2 players
    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //test #1
        printf("Check hand cards didn't change for Player %d\n", G.whoseTurn+1);
        for (i = 0; i < maxHandCount; i++)
        {
            //check hand card values
            printf("G.hand[%d][%d] = %d, expected = %d\n", G.whoseTurn, i, 
                    G.hand[G.whoseTurn][i], testG.hand[G.whoseTurn][i]);
            assertTrue(G.hand[G.whoseTurn][i], testG.hand[G.whoseTurn][i], 0);
        }
        //check hand card count
        if (G.whoseTurn == 0)
        {
            printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], 
                testG.handCount[G.whoseTurn]);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn], 0);
        }

        //test #2
        printf("Check deck cards didn't change for Player %d\n", G.whoseTurn+1);
        for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
        {
            //check deck values
            printf("G.deck[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.deck[G.whoseTurn][i],
                    testG.deck[G.whoseTurn][i]);
            assertTrue(G.deck[G.whoseTurn][i], testG.deck[G.whoseTurn][i], 0);
        }
        //check deck count
        if (G.whoseTurn == 0)
        {
            printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], 
                    testG.deckCount[G.whoseTurn]);
            assertTrue(G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn], 0);
        }

        //test #3
        printf("Check discard pile didn't change for Player %d\n", G.whoseTurn+1);
        for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
        {
            //check discard values
            printf("G.discard[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.discard[G.whoseTurn][i], 
                    testG.discard[G.whoseTurn][i]);
            assertTrue(G.discard[G.whoseTurn][i], testG.discard[G.whoseTurn][i], 0);
        }
        if (G.whoseTurn == 0)
        {
            //check discard count
            printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], 
                    testG.discardCount[G.whoseTurn]);
            assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn], 0);

            //test #4 any changes to victory
            printf("Test if there's any changes to victory supply count\n");
            for (i = 1; i < 4; i++)
            {
                printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
                assertTrue(G.supplyCount[i], testG.supplyCount[i], 0);
            }

            //test #5 any changes to kingdom card pile
            printf("Test if there's any changes to kingdom card pile\n");
            for (i = 0; i < 10; i++)
            {
                printf("G.supplyCount[%d] = %d, expected = %d\n", k[i], G.supplyCount[k[i]] ,testG.supplyCount[k[i]]);
                assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 0);
            }
        }
    }

    //print test result
    if (ERRORS == 0)
        printf("All tests passed!\n");
    else
        printf("Tests failed %d times\n", ERRORS);

    return 0;
}