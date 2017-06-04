#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
int value;
char suit [10];
char name [10];
}Card;

#define DECKSIZE 52
#define VALUE 9
#define FACE 4

void printDeck(Card cards[]);

void shuffle(Card cards[]);

void initDeck(Card cards[]);

int evaluateHand(Card hand[], int numCards);

void dealerBlackJack(Card player[], int playerCount, 
		     Card dealer[], int dealerCount);

void playHand (Card player[], int playerCount, 
               Card dealer[], int dealerCount,
               Card deck[], int cardsLeft);

