#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest5()
{    
    char *messagePrefix = "UNIT TEST 5 - Score For - Improper Count Check";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set discarded cards to have 2 estates worth 2 points
    G.discardCount[G.whoseTurn] = 2;
    for (int i = 0; i < G.discardCount[G.whoseTurn]; i++)
    {
        G.discard[G.whoseTurn][i] = estate;
    }

    //Set deck cards to have 8 estates worth 8 points
    G.deckCount[G.whoseTurn] = 4;
    for (int i = 0; i < G.deckCount[G.whoseTurn]; i++)
    {
        G.deck[G.whoseTurn][i] = estate;
    }

    int result = scoreFor(G.whoseTurn, &G);
    assert(result==10, "%s - End Score (%d) == Expected Score (%d)\n", messagePrefix, result, 10);
}

int main()
{
    unitTest5();
}