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

#define CARD "adventurer"

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