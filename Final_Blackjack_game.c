#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Function declarations
void shuffleDeck();
int dealCard();
int calculateHandValue(int hand[], int size);
int isBust(int hand[], int size);
char *getHandString(int hand[], int size);

// Game constants
#define MAX_HAND_SIZE 11 // Max cards a player can have (unlikely to exceed)

// Function to display the hand in a nice format
void displayHand(const char *title, int hand[], int handSize, int hideLastCard)
{
    printf("%s: %s", title, getHandString(hand, handSize - (hideLastCard ? 1 : 0)));
    if (!hideLastCard)
    {
        printf(" (%d)\n", calculateHandValue(hand, handSize));
    }
    else
    {
        printf("\n");
    }
}

// Function to get player input (Hit, Stand, Quit)
char getPlayerChoice()
{
    char response[10];
    char choice;

    while (1)
    {
        printf("(H)it, (S)tand or (Q)uit? ");
        if (fgets(response, sizeof(response), stdin) != NULL)
        {
            // Remove trailing newline
            response[strcspn(response, "\n")] = '\0';

            // Convert to lowercase for comparison
            for (int i = 0; response[i]; i++)
            {
                response[i] = tolower(response[i]);
            }

            // Check for full words or single letters
            if (strcmp(response, "hit") == 0 || strcmp(response, "h") == 0)
            {
                return 'h';
            }
            else if (strcmp(response, "stand") == 0 || strcmp(response, "s") == 0)
            {
                return 's';
            }
            else if (strcmp(response, "quit") == 0 || strcmp(response, "q") == 0)
            {
                return 'q';
            }
        }
        // Invalid response, prompt again
    }
}

// Dealer's play - dealer must hit until 17 or bust
void dealerPlay(int dealerHand[], int *dealerSize)
{
    printf("Dealer has: %s (%d)\n", getHandString(dealerHand, *dealerSize),
           calculateHandValue(dealerHand, *dealerSize));

    while (calculateHandValue(dealerHand, *dealerSize) <= 16)
    {
        dealerHand[*dealerSize] = dealCard();
        (*dealerSize)++;
        printf("Dealer has: %s (%d)\n", getHandString(dealerHand, *dealerSize),
               calculateHandValue(dealerHand, *dealerSize));
    }
}

// Main game loop
void playGame()
{
    int playerHand[MAX_HAND_SIZE];
    int dealerHand[MAX_HAND_SIZE];
    int playerSize = 0;
    int dealerSize = 0;
    char choice;

    // Deal initial 2 cards to each
    playerHand[0] = dealCard();
    playerSize = 1;
    playerHand[1] = dealCard();
    playerSize = 2;

    dealerHand[0] = dealCard();
    dealerSize = 1;
    dealerHand[1] = dealCard();
    dealerSize = 2;

    // Display initial hands
    printf("\nDealer has: ");
    printf("%s\n", getHandString(dealerHand, 1)); // Show only first card
    printf("Player has: %s (%d)\n", getHandString(playerHand, playerSize),
           calculateHandValue(playerHand, playerSize));

    // Player's turn
    while (1)
    {
        choice = getPlayerChoice();

        if (choice == 'q')
        {
            // Quit the game
            printf("\nThanks for playing!\n");
            exit(0);
        }

        if (choice == 'h')
        {
            // Hit - deal another card
            playerHand[playerSize] = dealCard();
            playerSize++;
            printf("Player has: %s (%d)\n", getHandString(playerHand, playerSize),
                   calculateHandValue(playerHand, playerSize));

            // Check if player bust
            if (isBust(playerHand, playerSize))
            {
                printf("You Lose\n\n");
                return; // Game over, will redeal
            }
        }

        if (choice == 's')
        {
            // Stand - reveal dealer's hand and play dealer's turn
            break;
        }
    }

    // Dealer's turn
    dealerPlay(dealerHand, &dealerSize);

    // Determine winner
    if (isBust(dealerHand, dealerSize))
    {
        printf("You Win!\n\n");
    }
    else
    {
        int playerValue = calculateHandValue(playerHand, playerSize);
        int dealerValue = calculateHandValue(dealerHand, dealerSize);

        if (playerValue > dealerValue)
        {
            printf("You Win!\n\n");
        }
        else
        {
            printf("You Lose\n\n");
        }
    }
}

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Initial shuffle
    shuffleDeck();

    // Main game loop - keep playing until player quits
    while (1)
    {
        playGame();
    }

    return 0;
}
