#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

//Council Room +4 cards +1 buy
int main (int argc, char** argv) {
    srand(time(NULL));
    int kingdom[10] = {adventurer, feast, council_room, village, remodel, mine, cutpurse, baron, tribute, smithy};
    int testSuccessful = 0;
    int testFailed = 0;
    int tests = 5000;
    struct gameState game;
    int myCard = council_room;
    int myChoice1 = -1;
    int myChoice2 = -1;
    int myChoice3 = -1;
    int myHandPos = -1;
    int* myBonus = 0;
    for(int i = 0; i < tests; i++) {
        int randomSeed = rand();//set random seed
        initializeGame(2, kingdom, randomSeed, &game);//Initialize the game
        int sizeOfDeck = rand() % (MAX_DECK + 1);
        int sizeOfHand = rand() % (sizeOfDeck + 1);
        game.deckCount[0] = sizeOfDeck - sizeOfHand;
        game.handCount[0] = sizeOfHand;
        int initialHandCt = game.handCount[0];
        int j = *game.handCount;
        cardEffect(myCard, myChoice1, myChoice2, myChoice3, &game, myHandPos, myBonus);
        int k = j+3;
        if(k == *game.handCount)
        {
            testSuccessful++;
        }
        else
        {
            testFailed++;
        }
    }
    printf("For Council Room Random Test Card 2:\n");
    printf("There were %d successful council room card plays", testSuccessful);
    printf("We had %d failures \n", testFailed);
    printf("Total games run: %d\n", tests);
    return 0;
}