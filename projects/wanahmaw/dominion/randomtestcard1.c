/* randomtestcard1.c
 * Randomly tests Smithy card
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define CARD "Smithy"
#define NOISY 1

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

void checkSmithyCard(struct gameState *post, int handPos, int p)
{
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));  // Copy gameState
    int r, i, bonus = 0;

    r = cardEffect(smithy, 0, 0, 0, post, handPos, &bonus); // Runs smithy

    // Draw 3 cards
    for (i = 0; i < 3; i++)
    {
        drawCard(p, &pre);
    }
    // Discard Smithy card
    discardCard(handPos, p, &pre, 0);

    // Check smithy function
    assertTrue(r, 0, 1);
    // Check hand count
    assertTrue(post->handCount[p], pre.handCount[p], 1);
    // Check deck count
    assertTrue(post->deckCount[p], pre.deckCount[p], 1);
    // Check discard count
    assertTrue(post->discardCount[p], pre.discardCount[p], 1);
}

int main()
{
    int i, n, p;
    int count = 8000, handPos = 0;
    struct gameState G;

    printf("Testing %s\nRANDOM TESTS\n", CARD);

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < count; n++) // Iterate random tests
    {
        printf("At %d...", n+1);
        for (i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256); // Randomize game
        }
        
        p = floor(Random() * MAX_PLAYERS);  // Set player
        G.whoseTurn = p;
        
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * (MAX_DECK-1));

        checkSmithyCard(&G, handPos, p);
    }

    if (!ERRORS)
        printf("********ALL TESTS PASSED!********\n\n");
    else
        printf("********TESTS FAILED %d times********\n\n", ERRORS);

    return 0;
}