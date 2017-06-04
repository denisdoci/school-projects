#include "bj.h"

void playHand (Card player[], int playerCount, 
               Card dealer[], int dealerCount,
               Card deck[], int cardsLeft)
{
  int playerPoints;
  int dealerPoints;
  int i;
  char input[100];

  do 
  {
    printf ("Do you want another card? (y/n):");
    gets(input);
    if (input[0] == 'y')
      player[playerCount++] = deck[--cardsLeft];

    printf ("Player\'s cards:\n");
    for ( i = 0; i < playerCount ; i++)
      printf ("  %s of %s\n", player[i].name, player[i].suit); 
    printf ("  Points: %d\n", evaluateHand(player, playerCount));
    printf ("Dealer shows: %s of %s\n", dealer[0].name, dealer[0].suit);
  }
  while (input[0] == 'y' && evaluateHand(player, playerCount) != -1);

  if(evaluateHand(player, playerCount) == -1)
  {
    printf ("Your point value went over 21.  You lose\n");
    return ;
  }

  printf ("\nDealer\'s cards:\n");
  for ( i = 0; i < dealerCount ; i++)
    printf ("  %s of %s\n", dealer[i].name, dealer[i].suit); 
  printf ("  Points: %d\n", evaluateHand(dealer, dealerCount));
  while (evaluateHand(dealer, dealerCount) < 17)
  {
    dealer[dealerCount++] = deck[--cardsLeft];
    printf ("  Newcard for dealer: %s of %s\n", 
            dealer[dealerCount - 1].name, dealer[dealerCount - 1].suit); 
    printf ("  Points: %d\n", evaluateHand(dealer, dealerCount));
    if (evaluateHand(dealer, dealerCount) == -1)
    {
      printf ("The dealer went over 21 points.  You win\n");
      return ;
    }
  }

  playerPoints = evaluateHand(player, playerCount);
  dealerPoints = evaluateHand(dealer, dealerCount);
  if (playerPoints == dealerPoints)
  {
    printf("Dealer and Player have the same point total.  Tie\n");
  }
  else if (playerPoints > dealerPoints)
  {
    printf("Player has the higher point total.  You win.\n");
  }
  else
  {
    printf("Dealer has the higher point total.  You lose.\n");
  }

}



int main(){

  Card deck[DECKSIZE];
  Card player[5];
  Card dealer[5];
  int cardsLeft;
  int playerCount;
  int dealerCount;
  int i;

  initDeck(deck);
  cardsLeft = 52;

  player[0] = deck[--cardsLeft];
  dealer[0] = deck[--cardsLeft];
  player[1] = deck[--cardsLeft];
  dealer[1] = deck[--cardsLeft];
  playerCount = 2;
  dealerCount = 2;

  printf ("Player\'s cards:\n");
  for ( i = 0; i < playerCount ; i++)
    printf ("  %s of %s\n", player[i].name, player[i].suit); 
  printf ("  Points: %d\n", evaluateHand(player, playerCount));
  printf ("Dealer shows: %s of %s\n", dealer[0].name, dealer[0].suit);
 
  if (evaluateHand(dealer, dealerCount) == 21)
  {
    dealerBlackJack(player, playerCount, dealer, dealerCount);
  }
  else if (evaluateHand(player, playerCount) == 21)
  {
    printf ("Player has Blackjack.  You win.\n");
  }
  else
  {
    playHand(player, playerCount, dealer, dealerCount, deck, cardsLeft);
  }

  return 0;
}
