/*
 * cardtest4.c
 * 
 * Include the following lines in your makefile:
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTEST "great hall"

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
    int i, discarded,   extraAction = 0;
    int handPos = 0, choice1 = 0, choice2 = 0, choice4 = 0, bonus = 0, newCards = 0;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game state to test case

    printf("TESTING CARD: %s\n", FUNCTEST);

    cardEffect(great_hall, choice1, choice2, choice4, &G, handPos, &bonus);

    //loop through players
    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //setup card movement for testing
        if (G.whoseTurn == 0)
        {
            extraAction = 1;    //card adds +1 action
            newCards = 1;       //card adds +1 card from deck
            discarded = 1;      //card is used then sent to played pile
        }
        else
        {
            extraAction = 0;
            newCards = 0;
            discarded = 0;
        }

        //============test 1============
        printf("Test player hand count: Player 1 is (Hand - 1 + 1). Player 2 is no change\n");
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], 
                testG.handCount[G.whoseTurn] + newCards - discarded);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn] + newCards - discarded, 1);

        //============test 2============
        printf("Test player's deck: Player 1 is (Deck - 1). Player 2 is no change\n");
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], (testG.deckCount[G.whoseTurn] - newCards));
        assertTrue(G.deckCount[G.whoseTurn], (testG.deckCount[G.whoseTurn] - newCards), 1);

        //============test 3============
        printf("Test player's played card pile: Player 1 is (+1). Player 2 is no change\n");
        printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, testG.playedCardCount + 1);
        assertTrue(G.playedCardCount, testG.playedCardCount + 1, 1);

        //============test 4============
        printf("Test player's # of actions: Player 1 is (+1)\n");
        if (G.whoseTurn == 0)
        {
            printf("G.numAction = %d, expected = %d\n", G.numActions, testG.numActions + extraAction);
            assertTrue(G.numActions, testG.numActions + extraAction, 1);
        }

        if (G.whoseTurn == 0)
        {
            //============test 5============
            printf("Test if there's any changes to victory supply count\n");
            for (i = 1; i < 4; i++)
            {
                printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
                assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
            }

            //============test 6============
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