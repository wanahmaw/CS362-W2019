/*
 * unittest3.c
 * 
 * Include the following lines in your makefile:
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define FUNCTEST "gainCard()"

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
    int i, r, supplyPos, toFlag;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, smithy, minion, council_room, feast, 
                gardens, village, remodel, mine, tribute};
    struct gameState G, testG;
    int maxHandCount = 5;
    initializeGame(numPlayers, k, seed, &G);        //create new game
    memcpy(&testG, &G, sizeof(struct gameState));   //copy game for comparison

    printf("TESTING %s:\n", FUNCTEST);

    //test ambassador since it wasn't in Kingdom set
    supplyPos = ambassador;
    toFlag = 0;
    G.whoseTurn = 0;
    printf("Test player %d gaining a card not in the Kingdom set\n", G.whoseTurn+1);
    r = gainCard(supplyPos, &G, toFlag, G.whoseTurn);
    printf("gainCard = %d, expected = -1\n", r);
    assertTrue(r, -1, 0);

    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //check if this card was sent to player's hand or discard pile
        printf("Test if card was sent to player %d's hand\n", G.whoseTurn+1);
        for (i = 0; i < maxHandCount; i++)
        {
            printf("G.hand[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.hand[G.whoseTurn][i], supplyPos);
            assertTrue(G.hand[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn]);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn], 0);

        //check if this card was sent to player's deck
        printf("Test if card was sent to player %d's deck\n", G.whoseTurn+1);
        for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
        {
            printf("G.deck[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.deck[G.whoseTurn][i], supplyPos);
            assertTrue(G.deck[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn]);
        assertTrue(G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn], 0);

        //check if this card was sent to player's discard pile
        printf("Test if card was sent to player %d's discard pile\n", G.whoseTurn+1);
        for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
        {
            printf("G.discard[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.discard[G.whoseTurn][i], supplyPos);
            assertTrue(G.discard[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);
        assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn], 0);

        //check if supply count went down
        if (G.whoseTurn == 0)
        {
            printf("Test if supply count went down\n");
            printf("G.supplyCount[%d] = %d, expected = %d\n", supplyPos, G.supplyCount[supplyPos], testG.supplyCount[supplyPos]);
            assertTrue(G.supplyCount[supplyPos], testG.supplyCount[supplyPos], 0);
        }  

        //test any changes to victory
        printf("Test if there's any changes to victory supply count");
        for (i = 1; i < 4; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
            assertTrue(G.supplyCount[i], testG.supplyCount[i], 0);
        }

        //test any changes to kingdom card pile
        printf("Test if there's any changes to kingdom card pile\n");
        for (i = 0; i < 10; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", k[i], G.supplyCount[k[i]] ,testG.supplyCount[k[i]]);
            assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 0);
        }
    }

    //test a smithy card supply count to 0
    memcpy(&G, &testG, sizeof(struct gameState));   //reset game
    supplyPos = smithy;
    G.supplyCount[supplyPos] = 0;
    toFlag = 1;
    G.whoseTurn = 0;
    printf("Test player %d gaining a Smithy with 0 supply count\n", G.whoseTurn+1);
    r = gainCard(supplyPos, &G, toFlag, G.whoseTurn);
    printf("gainCard = %d, expected = -1\n", r);
    assertTrue(r, -1, 0);

    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //check if this card was sent to player's hand or discard pile
        printf("Test if card was sent to player %d's hand\n", G.whoseTurn+1);
        for (i = 0; i < maxHandCount; i++)
        {
            printf("G.hand[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.hand[G.whoseTurn][i], supplyPos);
            assertTrue(G.hand[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn]);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn], 0);

        //check if this card was sent to player's deck
        printf("Test if card was sent to player %d's deck\n", G.whoseTurn+1);
        for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
        {
            printf("G.deck[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.deck[G.whoseTurn][i], supplyPos);
            assertTrue(G.deck[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn]);
        assertTrue(G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn], 0);

        //check if this card was sent to player's discard pile
        printf("Test if card was sent to player %d's discard pile\n", G.whoseTurn+1);
        for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
        {
            printf("G.discard[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.discard[G.whoseTurn][i], supplyPos);
            assertTrue(G.discard[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);
        assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn], 0);

        //check if supply count went down
        if (G.whoseTurn == 0)
        {
            printf("Test if supply count went down\n");
            printf("G.supplyCount[%d] = %d, expected = %d\n", supplyPos, G.supplyCount[supplyPos], 0);
            assertTrue(G.supplyCount[supplyPos], 0, 0);
        }

        //test any changes to victory
        printf("Test if there's any changes to victory supply count");
        for (i = 1; i < 4; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
            assertTrue(G.supplyCount[i], testG.supplyCount[i], 0);
        }

        //test any changes to kingdom card pile
        printf("Test if there's any changes to kingdom card pile\n");
        for (i = 0; i < 10; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", k[i], G.supplyCount[k[i]] ,testG.supplyCount[k[i]]);
            if (k[i] == smithy)
                break;
            assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 0);
        }
    }

    //test gaining a smithy card to deck
    memcpy(&G, &testG, sizeof(struct gameState));   //reset game
    supplyPos = smithy;
    toFlag = 1;
    G.whoseTurn = 0;
    printf("Test player %d gaining a smithy card to deck\n", G.whoseTurn+1);
    gainCard(supplyPos, &G, toFlag, G.whoseTurn);
    printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], 5+1);
    assertTrue(G.deckCount[G.whoseTurn], 5+1, 0);

    //check it's in the deck
    for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
    {
        printf("G.deck[%d][%d] = %d, expected = %d in pile\n", G.whoseTurn, i, G.deck[G.whoseTurn][i], supplyPos);
        if (G.deck[G.whoseTurn][i] != supplyPos && i == G.deckCount[G.whoseTurn] - 1)
        {
            printf("assert failed\n");
            ERRORS++;
        }
    }

    //check if it's sent to player's hand
    //check if it's sent to player's discard pile
    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //check if this card was sent to player's hand
        printf("Test if card was sent to player %d's hand\n", G.whoseTurn+1);
        for (i = 0; i < maxHandCount; i++)
        {
            printf("G.hand[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.hand[G.whoseTurn][i], supplyPos);
            assertTrue(G.hand[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn]);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn], 0);

        //check if this card was sent to player's discard pile
        printf("Test if card was sent to player %d's discard pile\n", G.whoseTurn+1);
        for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
        {
            printf("G.discard[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.discard[G.whoseTurn][i], supplyPos);
            assertTrue(G.discard[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);
        assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn], 0);

        //check if supply count went down
        if (G.whoseTurn == 0)
        {
            printf("Test if supply count went down\n");
            printf("G.supplyCount[%d] = %d, expected = %d\n", supplyPos, G.supplyCount[supplyPos], testG.supplyCount[supplyPos] - 1);
            assertTrue(G.supplyCount[supplyPos], testG.supplyCount[supplyPos] - 1, 0);
        }

        //test any changes to victory
        printf("Test if there's any changes to victory supply count");
        for (i = 1; i < 4; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
            assertTrue(G.supplyCount[i], testG.supplyCount[i], 0);
        }

        //test any changes to kingdom card pile
        printf("Test if there's any changes to kingdom card pile\n");
        for (i = 0; i < 10; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", k[i], G.supplyCount[k[i]] ,testG.supplyCount[k[i]]);
            if (k[i] == smithy)
                break;
            assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 0);
        }
    }

    //test gaining a smithy to player's hand
    memcpy(&G, &testG, sizeof(struct gameState));   //reset game
    supplyPos = smithy;
    toFlag = 2;
    G.whoseTurn = 0;
    printf("Test player %d gaining a smithy card to hand\n", G.whoseTurn+1);
    gainCard(supplyPos, &G, toFlag, G.whoseTurn);
    printf("G.handcount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], 5+1);
    assertTrue(G.handCount[G.whoseTurn], 5+1, 0);

    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //check if this card was sent to player's deck
        printf("Test if card was sent to player %d's deck\n", G.whoseTurn+1);
        for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
        {
            printf("G.deck[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.deck[G.whoseTurn][i], supplyPos);
            assertTrue(G.deck[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn]);
        assertTrue(G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn], 0);

        //check if this card was sent to player's discard pile
        printf("Test if card was sent to player %d's discard pile\n", G.whoseTurn+1);
        for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
        {
            printf("G.discard[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.discard[G.whoseTurn][i], supplyPos);
            assertTrue(G.discard[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);
        assertTrue(G.discardCount[G.whoseTurn], testG.discardCount[G.whoseTurn], 0);

        //check if supply count went down
        if (G.whoseTurn == 0)
        {
            printf("Test if supply count went down\n");
            printf("G.supplyCount[%d] = %d, expected = %d\n", supplyPos, G.supplyCount[supplyPos], testG.supplyCount[supplyPos] - 1);
            assertTrue(G.supplyCount[supplyPos], testG.supplyCount[supplyPos] - 1, 0);
        }

        //test any changes to victory
        printf("Test if there's any changes to victory supply count");
        for (i = 1; i < 4; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
            assertTrue(G.supplyCount[i], testG.supplyCount[i], 0);
        }

        //test any changes to kingdom card pile
        printf("Test if there's any changes to kingdom card pile\n");
        for (i = 0; i < 10; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", k[i], G.supplyCount[k[i]] ,testG.supplyCount[k[i]]);
            if (k[i] == smithy)
                break;
            assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 0);
        }
    }

    //test gaining a smithy  to player's discard pile
    memcpy(&G, &testG, sizeof(struct gameState));   //reset game
    supplyPos = smithy;
    toFlag = 0;
    G.whoseTurn = 0;
    printf("Test player %d gaining a smithy card to discard pile\n", G.whoseTurn+1);
    gainCard(supplyPos, &G, toFlag, G.whoseTurn);
    printf("G.discardCount[%d] = %d, expected = %d\n", G.whoseTurn, G.discardCount[G.whoseTurn], 1);
    assertTrue(G.discardCount[G.whoseTurn], 1, 0);

    for (G.whoseTurn = 0; G.whoseTurn < numPlayers; G.whoseTurn++)
    {
        //check if this card was sent to player's hand
        printf("Test if card was sent to player %d's hand\n", G.whoseTurn+1);
        for (i = 0; i < maxHandCount; i++)
        {
            printf("G.hand[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.hand[G.whoseTurn][i], supplyPos);
            assertTrue(G.hand[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.handCount[%d] = %d, expected = %d\n", G.whoseTurn, G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn]);
        assertTrue(G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn], 0);

        //check if this card was sent to player's deck
        printf("Test if card was sent to player %d's deck\n", G.whoseTurn+1);
        for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
        {
            printf("G.deck[%d][%d] = %d, expected != %d\n", G.whoseTurn, i, G.deck[G.whoseTurn][i], supplyPos);
            assertTrue(G.deck[G.whoseTurn][i], supplyPos, 1);
        }
        printf("G.deckCount[%d] = %d, expected = %d\n", G.whoseTurn, G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn]);
        assertTrue(G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn], 0);

        //check if supply count went down
        if (G.whoseTurn == 0)
        {
            printf("Test if supply count went down\n");
            printf("G.supplyCount[%d] = %d, expected = %d\n", supplyPos, G.supplyCount[supplyPos], testG.supplyCount[supplyPos] - 1);
            assertTrue(G.supplyCount[supplyPos], testG.supplyCount[supplyPos] - 1, 0);
        }

        //test any changes to victory
        printf("Test if there's any changes to victory supply count");
        for (i = 1; i < 4; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", i, G.supplyCount[i], testG.supplyCount[i]);
            assertTrue(G.supplyCount[i], testG.supplyCount[i], 0);
        }

        //test any changes to kingdom card pile
        printf("Test if there's any changes to kingdom card pile\n");
        for (i = 0; i < 10; i++)
        {
            printf("G.supplyCount[%d] = %d, expected = %d\n", k[i], G.supplyCount[k[i]] ,testG.supplyCount[k[i]]);
            if (k[i] == smithy)
                break;
            assertTrue(G.supplyCount[k[i]] ,testG.supplyCount[k[i]], 0);
        }
    }
    
     //print test result
    if (ERRORS == 0)
        printf("All tests passed!\n");
    else
        printf("Tests failed %d times\n", ERRORS);

    return 0;
}
