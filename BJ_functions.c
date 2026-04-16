#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Deck management
#define DECK_SIZE 52
int deck[DECK_SIZE];
int cardsInDeck;

void shuffleDeck()
{
    // Initialize deck with all 52 cards (13 cards × 4 suits)
    int cardIndex = 0;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int card = 1; card <= 13; card++)
        {
            deck[cardIndex++] = card;
        }
    }
    cardsInDeck = DECK_SIZE;

    // Shuffle using Fisher-Yates algorithm
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

int dealCard()
{
    // If deck is empty, shuffle it
    if (cardsInDeck == 0)
    {
        shuffleDeck();
    }
    // Deal the top card and remove it from deck
    return deck[--cardsInDeck];
}

int getCardRank(int deckCard)
{
    return (deckCard % 13) + 1;
}

int getCardSuit(int deckCard)
{
    return deckCard / 13;
}

int getCardValue(int card)
{
    // For deck cards (0-51), extract the rank
    int rank = (card % 13) + 1;

    if (rank >= 2 && rank <= 10)
    {
        return rank; // Cards 2-10 are worth their face value
    }
    else if (rank >= 11 && rank <= 13)
    {
        return 10; // Jack, Queen, King are worth 10
    }
    else if (rank == 1)
    {
        return 11; // Ace is worth 11 by default
    }
    return 0; // Invalid card
}
int calculateHandValue(int hand[], int size)
{
    int totalValue = 0;
    int aceCount = 0;

    for (int i = 0; i < size; i++)
    {
        int rank = (hand[i] % 13) + 1;
        int cardValue = getCardValue(hand[i]);
        totalValue += cardValue;
        if (rank == 1)
        { // Count Aces
            aceCount++;
        }
    }

    // Adjust for Aces if total value exceeds 21
    while (totalValue > 21 && aceCount > 0)
    {
        totalValue -= 10; // Treat Ace as 1 instead of 11
        aceCount--;
    }

    return totalValue;
}

int isBust(int hand[], int size)
{
    return calculateHandValue(hand, size) > 21;
}
char getSuitChar(int suit)
{
    switch (suit)
    {
    case 0:
        return 's'; // spades
    case 1:
        return 'h'; // hearts
    case 2:
        return 'c'; // clubs
    case 3:
        return 'd'; // diamonds
    default:
        return '?';
    }
}

char getRankChar(int rank)
{
    if (rank == 1)
        return 'A';
    if (rank >= 2 && rank <= 9)
        return '0' + rank; // Returns '2' through '9'
    if (rank == 10)
        return 'T'; // T for 10
    if (rank == 11)
        return 'J';
    if (rank == 12)
        return 'Q';
    if (rank == 13)
        return 'K';
    return '?';
}

char *getCardName(int deckCard)
{
    static char name[4];
    int rank = getCardRank(deckCard);
    int suit = getCardSuit(deckCard);

    if (rank == 10)
    {
        snprintf(name, sizeof(name), "10%c", getSuitChar(suit));
    }
    else
    {
        snprintf(name, sizeof(name), "%c%c", getRankChar(rank), getSuitChar(suit));
    }
    return name;
}

char *getHandString(int hand[], int size)
{
    static char handString[500];
    handString[0] = '\0'; // Clear the string

    for (int i = 0; i < size; i++)
    {
        strcat(handString, getCardName(hand[i]));
        if (i < size - 1)
        {
            strcat(handString, " ");
        }
    }
    return handString;
}