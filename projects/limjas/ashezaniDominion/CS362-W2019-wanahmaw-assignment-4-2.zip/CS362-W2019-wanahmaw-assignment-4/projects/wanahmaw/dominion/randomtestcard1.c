#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//Smithy Test +3 cards
int main() {
    struct gameState game;
    int randSeed = 10000;
    srand(time(NULL));
    int currentplayer = 0;
    int kingdom[10] = {adventurer, feast, gardens, village, remodel, mine, cutpurse, baron, tribute, smithy};
    int myCard = smithy;
    int myChoice1 = -1;
    int myChoice2 = -1;
    int myChoice3 = -1;
    int myHandPos = -1;
    int* myBonus = 0;
    int initialHandCt;
    int afterHandCt;
    int failureDrawingCard = 0;
    int testPassed = 0;
    //randomize hand size
    for(int i = 0; i < 150000; i++) {
        initializeGame(2, kingdom, randSeed, &game);
        int sizeOfDeck = rand() % (MAX_DECK + 1);
        int sizeOfHand = rand() % (sizeOfDeck + 1);
        game.deckCount[0] = sizeOfDeck - sizeOfHand;
        game.handCount[0] = sizeOfHand;
        initialHandCt = game.handCount[0];
        cardEffect(myCard, myChoice1, myChoice2, myChoice3, &game, myHandPos, myBonus);
        afterHandCt = game.handCount[0];
        if (afterHandCt != (initialHandCt + 2)) {
            printf("Incorrect amount of cards drawn: Test Failed\n\n");
            failureDrawingCard++;
        }
        else {
            printf("Tests Passed\n");
            testPassed++;
        }
    }
    printf("\nFor Smithy Random Test Card 1: Test passed: %d tests\n", testPassed);
    printf("Failures for drawing: %d\n",failureDrawingCard);
    return 0;
}