#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest10()
{
    printf("Starting Unit Test 10 - Ambassador card - comparing position i with card choice \n\n");

    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, ambassador, smithy};

    initializeGame(2, k, 1234, &pre);

    printf("Game initialized \n\n");

    int bonus = 0,
        r = 10;

    pre.handCount[pre.whoseTurn] = r;

    // randomly assign cards to player and other player
    for (int i = 0; i < r; i++)
    {
        pre.hand[pre.whoseTurn][i] = k[9 - i];
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Choose to discard 1 copper card. \n\n");

    int choice1 = 8,
        choice2 = 1;

    // set 3 duplicate copper cards in deck
    post.hand[post.whoseTurn][9] = copper;
    post.hand[post.whoseTurn][8] = copper;
    post.hand[post.whoseTurn][7] = copper;

    // call the cardEffect function
    cardEffect(ambassador, choice1, choice2, 0, &post, 0, &bonus);

    // assert the results
    int i = 0;
    int copperCount = 0;

    for (int i = 0; i < r; i++)
    {
        printf("%d \n", post.hand[post.whoseTurn][i]);
    }

    while (i < r)
    {
        if (post.hand[post.whoseTurn][i] == copper)
        {
            copperCount++;
        }
        i++;
    }

    if (copperCount == 2)
    {
        printf("Bug found! Wrong card discarded! \n");
        printf("Pre-call copper cards tally: %d \n", 3);
        printf("Post-call copper cards tally: %d \n\n", copperCount);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Choose to discard two copper cards. \n\n");

    choice1 = 8;
    choice2 = 2;

    // set 3 duplicate copper cards in deck
    post.hand[post.whoseTurn][9] = copper;
    post.hand[post.whoseTurn][8] = copper;
    post.hand[post.whoseTurn][7] = copper;

    // call the cardEffect function
    cardEffect(ambassador, choice1, choice2, 0, &post, -1, &bonus);

    // assert the results
    i = 0;
    copperCount = 0;
    while (i < r - choice2)
    {
        if (post.hand[post.whoseTurn][i] == copper)
        {
            copperCount++;
        }
        i++;
    }

    if (copperCount != 1)
    {
        printf("Bug found! Wrong card discarded! \n");
        printf("Pre-call copper cards tally: %d \n", 3);
        printf("Post-call copper cards tally: %d \n\n", copperCount);
    }

    if (post.handCount[post.whoseTurn] == pre.handCount[post.whoseTurn] - 2)
    {
        printf("Bug found! Number of cards on hand should be decremented by 2! \n");
        printf("Pre-call number of cards on hand: %d \n", pre.handCount[post.whoseTurn]);
        printf("Post-call number of cards on hand: %d \n\n", post.handCount[post.whoseTurn]);
    }

    printf("Unit Test 10 completed! \n\n");
}

int main()
{
    unitTest10();
}