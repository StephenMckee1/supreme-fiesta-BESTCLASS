#ifndef BJ_FUNCTIONS_H
#define BJ_FUNCTIONS_H

// Deck management
void shuffleDeck();
int dealCard();
int getCardRank(int deckCard);
int getCardSuit(int deckCard);
int getCardValue(int card);
int calculateHandValue(int hand[], int size);
int isBust(int hand[], int size);

// Card display
char *getSuitChar(int suit);
char getRankChar(int rank);
char *getCardName(int deckCard);
char *getHandString(int hand[], int size);

#endif