#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//Adventurer Test mandatory
int main() {
    struct gameState game;
    int randSeed = 10000;
    srand(time(NULL));
    int currentplayer = 0;
    int kingdom[10] = {adventurer, feast, gardens, village, remodel, mine, cutpurse, baron, tribute, smithy};
    int sizeOfDeck = rand() % (MAX_DECK + 1);
    int sizeOfHand = rand() % (sizeOfDeck + 1);
    int randomCard = rand() % (50 + 1);;
    int randomKingdomCard = rand() % (10);
    int myCard = adventurer;
    int myChoice1 = -1;
    int myChoice2 = -1;
    int myChoice3 = -1;
    int myHandPos = -1;
    int* myBonus = 0;
    int coinsCount1 = 0;
    int coinsCount2 = 0;
    int testPassed = 0;
    int failureDrawingCard = 0;
    //randomize hand size
    for(int i = 0; i < 15000; i++){ //for 100 rand tests
        initializeGame(2, kingdom, randSeed, &game); //initialize game
        game.deckCount[0] = sizeOfDeck - sizeOfHand;
        game.handCount[0] = sizeOfHand;
        for (int j = 0; j < 2; j++){ //initialize random decks
            for(int k = 0; k < game.deckCount[j]; k++){
                if(randomCard == 0){
                    game.deck[j][k] = copper;
                }
                else if(randomCard == 1){
                    game.deck[j][k] = silver;
                }
                else if(randomCard == 2){
                    game.deck[j][k] = gold;
                }
                else {
                    game.deck[j][k] = kingdom[randomKingdomCard];
                }
            }
        }
        for(int i = 0; i < game.handCount[currentplayer]; i++){
            if(game.hand[currentplayer][i] == copper || game.hand[currentplayer][i] == silver || game.hand[currentplayer][i] == gold){
                coinsCount1++;
            }
        }
        cardEffect(myCard, myChoice1, myChoice2, myChoice3, &game, myHandPos, myBonus);
        for(int j = 0; j < game.handCount[currentplayer]; j++){
            if(game.hand[currentplayer][j] == copper || game.hand[currentplayer][j] == silver || game.hand[currentplayer][j] == gold){
                coinsCount2++;
            }
        }
        if(coinsCount2 > (coinsCount1 + 2)){
            printf("Test Failed too many cards\n\n");
            failureDrawingCard++;
        }
        else if(coinsCount2 < coinsCount1){
            printf("Test Failed too few cards\n\n");
            failureDrawingCard++;
        }
        else{
            printf("All Tests: Passed\n\n");
            testPassed++;
        }
    }
    printf("\nAdventurer Card test Random Test Adventurer:\n Test passed: %d tests\n", testPassed);
    printf("Failures for drawing: %d\n",failureDrawingCard);
    return 0;
}