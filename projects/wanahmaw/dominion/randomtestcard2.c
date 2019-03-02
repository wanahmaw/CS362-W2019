/* randomtestcard2.c
 * Randomly tests Council room
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define CARD "Council Room"
#define NOISY 0

int ERRORS = 0; // Global error counter

// Assertion function that doesn't stop program when assertion fails
void assertTrue (int a, int b, int equal)
{
    if (!equal && a == b)
    {
        //printf("assert failed\n");
        ERRORS++;
    }
    else if (equal && a != b)
    {
        //printf("assert failed\n");
        ERRORS++;
    }
}

void checkCouncilRoom(struct gameState *post, int p, int handPos) {
    struct gameState pre;
    int i, r, players;
    int bonus = 0;

    memcpy (&pre, post, sizeof(struct gameState));  // Copy gameState

    r = cardEffect(council_room, 0, 0, 0, post, handPos, &bonus);   // Run Council room

    for (i = 0; i < 4; i++) {   // Draw 4 cards
        drawCard(p, &pre);
    }

    pre.numBuys++;  // Add 1 extra buy

    // Each other player draws a card
    for (i = 0; i < pre.numPlayers; i++) {
        if (pre.whoseTurn != i) {
            drawCard(i, &pre);
        }
    }
    discardCard(handPos, p, &pre, 0);   // Discard played Council Room card

    // Check Council Room card
    assertTrue(r, 0, 1);
    // Check number of buys
    assertTrue(post->numBuys, pre.numBuys, 1);

    //if (NOISY) printf("handcount check for player %d\n");

    // Check hand, deck, and discard count for all players
    players = post->numPlayers;
    for (i = 0; i < players; i++) {
        assertTrue(post->handCount[i], pre.handCount[i], 1);
        assertTrue(post->deckCount[i], pre.deckCount[i], 1);
        assertTrue(post->discardCount[i], pre.discardCount[i], 1);
    }
}

int main() {
    int i, n, p;
    int count = 8000, handPos = 0;
    struct gameState G;

    printf("Testing %s\nRANDOM TESTS\n", CARD);

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < count; n++) {   // Iterate random tests
        if (NOISY) printf("At %d...", n+1);

        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256); // Randomize game
        }

        // Set number of players (min of 2) and main player
        G.numPlayers = floor(Random() * ((MAX_PLAYERS - 2) + 1) + 2);
        if (NOISY) printf("%d players\t", G.numPlayers);
        p = floor(Random() * G.numPlayers);  // Set player
        G.whoseTurn = p;

        // Set sane game conditions
        G.numBuys = 1;
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        do {
            G.handCount[p] = floor(Random() * MAX_HAND);
        } while (G.handCount[p] > 496);

        // Set deck, discard, and hand count for all players
        for (i = 0; i < G.numPlayers; i++) {
            if (i != p) {
                G.deckCount[i] = G.deckCount[p];
                G.discardCount[i] = G.discardCount[p];
                G.handCount[i] = G.handCount[p];
            }
        }
        G.playedCardCount = floor(Random() * (MAX_DECK-1));

        if (NOISY) {
            printf("Initial hand count:\t");
            for (i = 0; i < G.numPlayers; i ++) {
                printf("G.handCount[%d] = %d\n", i, G.handCount[i]);
            }
            printf("\n");
        }

        checkCouncilRoom(&G, p, handPos);
    }

    if (!ERRORS)
        printf("********ALL TESTS PASSED!********\n\n");
            else
        printf("********TESTS FAILED %d times********\n\n", ERRORS);

    return 0;
}
