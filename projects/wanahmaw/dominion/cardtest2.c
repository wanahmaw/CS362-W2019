/*
 * cardtest2.c
 * 
 * Include the following lines in your makefile:
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTEST "adventurer"

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
    int i, discarded, cardDrawn;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, newCards = 0;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game state to test case

    printf("TESTING CARD: %s\n", FUNCTEST);

    cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);

    //loop over 2 players
    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //set new card + 2 & discard +1 for player 1
        if (G.whoseTurn == 0)
        {
            newCards = 2;
            discarded = 1;
        }
        else
        {
            newCards = 0;
            discarded = 0;
        }

        //============test 1============
        printf("Test players hand count: Player 1 is (2 - 1). Player 2 is (0 - 0)\n");
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], 
                testG.handCount[G.whoseTurn] + newCards - discarded);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn] + newCards - discarded, 1);

        //============test 2============
        printf("Test player 1's newest 2 cards in hand are treasure cards. Player 2 no change\n");
        for (i = 0; i < 2; i++)
        {
            cardDrawn = G.hand[G.whoseTurn][G.handCount[G.whoseTurn] - (i+1)];
            printf("Player %d's card #%d drawn in hand = %d, expected = 4, 5, or 6\n", G.whoseTurn+1, i+1, cardDrawn);
            if (cardDrawn != copper || cardDrawn != silver || cardDrawn != gold)
                assertTrue(cardDrawn, 999, 0); //illicit error message
        }

        //============test 3============
        printf("Test player 1's discard pile didn't include a treasure card. Player 2 no change\n");
        for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
        {
            cardDrawn = G.discard[G.whoseTurn][i];
            printf("G.discard[%d][%d] = %d, expected != 4, 5, or 6\n", G.whoseTurn, i, cardDrawn);
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                assertTrue(cardDrawn, -999, 1); //illicit error message
        }
        if (G.whoseTurn == 1)
        {
            printf("Test player 2 doesn't have any discard card\n");
            printf("G.discardCount[%d] = %d, expected = 0\n", G.whoseTurn, G.discardCount[G.whoseTurn]);
        }

        //============test 4============
        printf("Test player 1's deck pile (- 2 treasure cards - %d discard pile). Player2 no change\n", G.discardCount[0]);
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], (testG.deckCount[G.whoseTurn] - newCards - G.discardCount[G.whoseTurn]));
        assertTrue(G.deckCount[G.whoseTurn], (testG.deckCount[G.whoseTurn] - newCards - G.discardCount[G.whoseTurn]), 1);

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