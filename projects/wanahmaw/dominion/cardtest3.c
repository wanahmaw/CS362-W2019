/*
 * cardtest3.c
 * 
 * Include the following lines in your makefile:
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTEST "council room"

int ERRORS = 0; //global error count

void assertTrue (int a, int b, int equal)
{
    if (!equal && a == b)
    {
        printf("assert failed\n");
        ERRORS++;
    }
    else if (equal && a != b)
    {
        printf("assert failed\n");
        ERRORS++;
    }
}

int main()
{
    int i, discarded, buyCount;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, newCards = 0;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game state to test case

    printf("TESTING CARD: %s\n", FUNCTEST);

    cardEffect(council_room, choice1, choice2, choice3, &G, handPos, &bonus);

    //loop over 2 players
    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //setup card movement for testing
        if (G.whoseTurn == 0)
        {
            newCards = 4;
            buyCount = 1;
            discarded = 1;
        }
        else
        {
            newCards = 1;
            buyCount = 0;
            discarded = 0;
        }
        
        //============test 1============
        printf("Test player hand count: Player 1 is (4 - 1). Player 2 is (1 - 0)\n");
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], 
                testG.handCount[G.whoseTurn] + newCards - discarded);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn] + newCards - discarded, 1);

        //============test 2============
        printf("Test player's deck: Player 1 is (Deck - 4). Player 2 is no change\n");
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], (testG.deckCount[G.whoseTurn] - newCards));
        assertTrue(G.deckCount[G.whoseTurn], (testG.deckCount[G.whoseTurn] - newCards), 1);

        /*============test 3============ figured council room went into played card pile, not discard pile
        printf("Test player's discard pile: Player 1 is (+1). Player 2 is no change\n");
        printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);
        assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn], 1);
        */

        //============test 4============
        printf("Test player's played card pile: Player 1 is (+1). Player 2 is no change\n");
        printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, testG.playedCardCount + 1);
        assertTrue(G.playedCardCount, testG.playedCardCount + 1, 1);

        //============test 5============
        printf("Test player's buy count: Player1 is (+1). Player 2 is no change\n");
        printf("Player %d: G.numBuys = %d, expected = %d\n", G.whoseTurn, G.numBuys, testG.numBuys + buyCount);
        assertTrue(G.numBuys, testG.numBuys + buyCount, 1);

        if (G.whoseTurn == 0)
        {
            //============test 6============
            printf("Test if there's any changes to victory supply count\n");
            for (i = 1; i < 4; i++)
            {
                printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
                assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
            }

            //============test 7============
            printf("Test if there's any changes to kingdom card pile\n");
            for (i = 0; i < 10; i++)
            {
                printf("G.supplyCount[k[%d]] = %d, expected = %d\n", k[i], G.supplyCount[k[i]], testG.supplyCount[k[i]]);
                assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 1);
            }
        }
    }


    //print test result
    if (ERRORS == 0)
        printf("******ALL TESTS PASSED!******\n");
    else
        printf("******Tests FAILED %d times******\n", ERRORS);

    return 0;
}