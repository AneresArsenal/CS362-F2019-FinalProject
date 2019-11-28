#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest9()
{
    printf("Starting Unit Test 9 - Tribute card - duplicate revealed cards \n\n");

    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int tributeRevealedCards[2] = {-1, -1};

    initializeGame(2, k, 1234, &pre);

    printf("Game initialized \n\n");

    //Set discard pile to zero.
    pre.discardCount[pre.whoseTurn] = 0;
    pre.discard[pre.whoseTurn][0] = -1;

    int handPos = 0,
        currentPlayer = 0,
        bonus = 0,
        r = 10;

    int nextPlayer = pre.whoseTurn + 1;

    //Set first cards in hand to feast and silver
    pre.handCount[pre.whoseTurn] = r;
    pre.handCount[nextPlayer] = r;
    // pre.hand[pre.whoseTurn][0] = tribute;

    // randomly assign cards to player and other player
    for (int i = 0; i < r; i++)
    {
        pre.hand[currentPlayer][i] = k[9 - i];
        pre.hand[nextPlayer][i] = k[9 - i];
    }

    // set test variables
    pre.numActions = 2;
    pre.coins = 2;

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Reveal and discard top 2 cards (1 action card and 1 treasure card) from next player's hand. \n\n");

    // set top 2 cards
    post.hand[nextPlayer][9] = village;
    post.hand[nextPlayer][8] = copper;

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    // assert the results
    // copper coin (treasure card) should increase coins by 2
    if (bonus != 2)
    {
        printf("Bug #1 found! Wrong amount of bonus added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    // village card (action card) should increase action plays by 1 (
    //deduct one for current phase and + 2 action phases)
    if (post.numActions != pre.numActions + 1)
    {
        printf("Bug #2 found! Number of action plays not incremented by 1! \n");
        printf("Pre-call number of action plays: %d \n", pre.numActions);
        printf("Post-call number of action plays: %d \n\n", post.numActions);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Reveal and discard top 2 cards from next player's hand with victory cards only. \n\n");

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    post.hand[nextPlayer][9] = estate;
    post.hand[nextPlayer][8] = estate;

    // assert the results
    // adds only 2 cards to current player's deck and deduct 1 tribute card played
    // (net 1 additional card)
    if (post.handCount[currentPlayer] == pre.handCount[currentPlayer] + 1)
    {
        printf("Valid! Number of cards in player's hand is accurate! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 3: Reveal and discard top 2 cards from next player's hand with action cards only. \n\n");

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    post.hand[nextPlayer][9] = minion;
    post.hand[nextPlayer][8] = minion;

    // assert the results
    // adds only 2 action phases to current player's deck and deduct 1 action phase played
    // (net 1 action phase)
    if (post.numActions == pre.numActions + 1)
    {
        printf("Valid! Number of cards in player's hand is accurate! \n");
        printf("Pre-call handCount: %d \n", pre.numActions);
        printf("Post-call handCount: %d \n\n", post.numActions);
    }

    printf("Unit Test 9 completed! \n\n");
}

int main()
{
    unitTest9();
}