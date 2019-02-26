/* randomtestadventurer.c
 * Randomly tests Adventurer card
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define CARD "Adventurer"
#define NOISY 0

int ERRORS = 0; // Global error counter

// Assertion function that doesn't stop program when assertion fails
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

void checkAdventurerCard(struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));  // Copy gameState
    int temphand[MAX_HAND];
    int p = pre.whoseTurn;
    int bonus = 0, drawntreasure = 0, cardDrawn = -999, i, r;
    int preTreasureHand = 0, postTreasureHand = 0, z = 0;

    r = cardEffect(adventurer, 0, 0 ,0, post, 0, &bonus);   // Runs adventurer

    while (drawntreasure < 2) {
        if (pre.deckCount[p] < 1) { // If deck is empty we need to shuffle discard & add to deck
            shuffle(p, &pre);
        }
        drawCard(p, &pre);  // Drawn card is placed on top of hand
        cardDrawn = pre.hand[p][pre.handCount[p] - 1];  // Get top most card in hand
        // Check for treasure card
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else {
            temphand[z] = cardDrawn;
            pre.handCount[p]--; // Removes the top card that's recently drawn
            z++;
        }
        while (z - 1 >= 0) {
            pre.discard[p][pre.discardCount[p]++] = temphand[z - 1]; // Discard all drawn cards in play
            z--;
        }
    }
    // Test card effect
    assertTrue(r, 0, 1);
    // Test hand count
    if (NOISY)
        printf("Post hand: %d\tPre hand: %d\n", post->handCount[p], pre.handCount[p]);
    assertTrue(post->handCount[p], pre.handCount[p], 1);
    // Test deck count
    if (NOISY)
        printf("Post deck: %d\tPre deck: %d\n", post->deckCount[p], pre.deckCount[p]);
    assertTrue(post->deckCount[p], pre.deckCount[p], 1);
    // Test discard count
    if (NOISY)
        printf("Post discard: %d\tPre discard: %d\n", post->discardCount[p], pre.discardCount[p]);
    assertTrue(post->discardCount[p], pre.discardCount[p], 1);
    // Test treasure cards
    for (i = 0; i < post->handCount[p]; i++) {
        cardDrawn = post->hand[p][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            postTreasureHand++;
    }
    for (i = 0; i < pre.handCount[p]; i++) {
        cardDrawn = pre.hand[p][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            preTreasureHand++;
    }
    if (NOISY)
        printf("Post treasure: %d\tPre treasure: %d\n", postTreasureHand, preTreasureHand);
    assertTrue(postTreasureHand, preTreasureHand, 1);
}

int main()
{
    int i, n, p;
    int count = 8000;
    struct gameState G;

    printf ("Testing %s\nRANDOM TESTS\n", CARD);

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < count; n++) // Iterate random tests
    {   
        if (NOISY) printf("At %d...", n+1);
        for (i = 0; i < sizeof(struct gameState); i++)
            ((char*)&G)[i] = floor(Random() * 256); // Randomize game state

        p = floor(Random() * MAX_PLAYERS);    // Set player
        G.whoseTurn = p;

        G.deckCount[p] = floor(Random() * ((MAX_DECK - 3) + 1) + 3);    // Set deck count, must have something there
        G.discardCount[p] = 0;  // Set discard count 0 for new round
        G.handCount[p] = floor(Random() * ((MAX_HAND - 3) + 1) + 3);    // Set hand count, must have something there

        // Fill at least 3 treasure cards in deck
        for (i = 0; i < 3; i++)
            G.deck[p][i] = copper;

        // TO-DO checkAdventurerard(&G);
        if (NOISY) {
            printf("Deck: %d\tDeck: %d\tHand: %d\tPlayer: %d\t", G.deckCount[p], G.deckCount[p], G.handCount[p], p);
        }
        checkAdventurerCard(&G);
        if (NOISY) printf("ERRORS = %d\n", ERRORS);
    }

    if (!ERRORS)
        printf("********ALL TESTS PASSED!********\n\n");
    else
        printf("********TESTS FAILED %d times********\n\n", ERRORS);

    return 0;
}