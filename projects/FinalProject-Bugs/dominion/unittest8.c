#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest8a()
{
    printf("--------------------- Project Bug #8 ------------------------\n");
    char *messagePrefix = "UNIT TEST 8A - playCard/cardEffect - Coin Tracking Issues";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;
    G.hand[G.whoseTurn][1] = estate;
    G.hand[G.whoseTurn][2] = copper;
    G.handCount[G.whoseTurn] = 3;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, 1, 0, 0, &G);

    assert(G.coins == (preG.coins + 4), "%s - End Num Coins (%d) == Start Num Coins + 4 (%d)\n", messagePrefix, G.coins, (preG.coins + 4));


    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #8 <<<<<<<<<<<<<<<<<<< \n\n");
}

int main()
{
    unitTest8a();
}