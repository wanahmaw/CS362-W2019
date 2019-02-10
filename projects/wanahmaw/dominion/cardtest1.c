/*
 * cardtest1.c
 * 
 * Include the following lines in your makefile:
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTEST "smithy"

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
    int i, discarded;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, newCards = 0;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game state to test case

    printf("TESTING CARD: %s\n", FUNCTEST);

    cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);

    //loop over 2 players
    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //set new card +3 & discard +1 for player1
        if (G.whoseTurn == 0)
        {
            newCards = 3;   //adds 3 cards from deck to hand
            discarded = 1;  //discard smithy once played
        }
        else
        {
            newCards = 0;
            discarded = 0;
        }

        //============test 1============
        printf("Test players hand count: Player 1's hand count (3 - 1). Player 2's hand count (0 - 0)\n");
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], 
                testG.handCount[G.whoseTurn] + newCards - discarded);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn] + newCards - discarded, 1);
        
        //============test 2============
        printf("Test 3 cards removed from player 1's deck pile. 0 from player 2's deck pile\n");
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn] - newCards);
        assertTrue(G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn] - newCards, 1);

        //============test 3============
        printf("Test 1 card added into player 1's discard pile. 0 for player 2's discard pile\n");
        printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn] + discarded);
        assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn] + discarded, 1);

        if (G.whoseTurn == 0)
        {
            //============test 4============
            printf("Test if there's any changes to victory supply count\n");
            for (i = 1; i < 4; i++)
            {
                printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
                assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
            }

            //============test 5============
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