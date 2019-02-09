/*
 * unittest2.c
 * 
 * Include the following lines in your makefile:
 * unittest2: unittest.1.c dominion.o rngs.o
 *      gcc -o unittest.1 -g unittest.1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define FUNCTEST "handCard()"

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
    int i, r, p, handPos;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;
    int maxHandCount = 5;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game for comparison
    //create test hand for both players
    int testHand1[maxHandCount];
    int testHand2[maxHandCount];
    //create cards for player 1's hand
    testHand1[0] = adventurer;
    testHand1[1] = province;
    testHand1[2] = gold;
    testHand1[3] = adventurer;
    testHand1[4] = gold;
    //create cards for player 2's hand
    testHand2[0] = copper;
    testHand2[1] = estate;
    testHand2[2] = village;
    testHand2[3] = tribute;
    testHand2[4] = silver;
    //give cards to each player
    G.handCount[0] = maxHandCount;
    G.handCount[1] = maxHandCount;
    memcpy(G.hand[0], testHand1, sizeof(int) * maxHandCount); // player 1 hands
    memcpy(G.hand[1], testHand2, sizeof(int) * maxHandCount); // player 2 hands

    printf("TESTING %s:\n", FUNCTEST);
    for (p = 0; p < numPlayers; p++)
    {
        G.whoseTurn = p;
        for (handPos = 1; handPos <= maxHandCount; handPos++)
        {
                printf("Test player %d's card in hand position %d\n", p+1, handPos);
                r = handCard(handPos-1, &G);
                if (p == 0)
                {
                    printf("handCard = %d, expected = %d\n", r, testHand1[handPos-1]);
                    assertTrue(r, testHand1[handPos-1]);
                }
                else
                {
                    printf("handCard = %d, expected = %d\n", r, testHand2[handPos-1]);
                    assertTrue(r, testHand2[handPos-1]);
                }
                
        }
    }

    //check if game state changed for player 1 or 2's cards
    for (p = 0; p < numPlayers; p++)
    {
        G.whoseTurn = p;
        //check # cards in hand didn't change
        printf("Test player %d has same # of cards in hand\n", p+1);
        printf("numHandCards = %d, expected = %d\n", numHandCards(&G), maxHandCount);
        assertTrue(numHandCards(&G), maxHandCount);

        // check cards in hand didn't change !
        if (p == 0)
        {
            printf("Test cards in player %d didn't change\n", p+1);
            for (i = 0; i < 5; i++)
            {
                printf("G.hand[%d][%d] = %d, expected = %d\n", p, i, G.hand[p][i], testHand1[i]);
                assertTrue(G.hand[p][i], testHand1[i]);
            }
        }
        else
        {
            printf("Test cards in player %d didn't change\n", p+1);
            for (i = 0; i < 5; i++)
            {
                printf("G.hand[%d][%d] = %d, expected = %d\n", p, i, G.hand[p][i], testHand2[i]);
                assertTrue(G.hand[p][i], testHand2[i]);
            }
        }
        // check victory & kingdom card piles didn't change 1
    }

    //print test result
    if (ERRORS == 0)
        printf("All tests passed!\n");
    else
        printf("Tests failed %d times\n", ERRORS);
    
    return 0;
}