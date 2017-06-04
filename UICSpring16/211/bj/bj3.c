#include "bj.h"

int evaluateHand(Card hand[], int numCards)
{
  int points = 0;
  int i;

  for (i = 0; i < numCards; i++)
  {
    points = points + hand[i].value;
  }

  for (i = 0; i < numCards; i++)
  {
    if (points > 21 && hand[i].value == 11)
       points = points - 10;
  }

  if (points > 21)
   points = -1;

  return points;  
}

void dealerBlackJack(Card player[], int playerCount, 
                     Card dealer[], int dealerCount)
{
  int i;

  printf ("Dealer\'s cards:\n");
  for ( i = 0; i < dealerCount ; i++)
    printf ("  %s of %s\n", dealer[i].name, dealer[i].suit); 
  printf ("  Points: %d\n", evaluateHand(dealer, dealerCount));

  if (evaluateHand(player, playerCount) == 21)
  {
    printf ("Both Dealer and Player have Blackjack.  Tie\n");
  }
  else
  {
    printf ("The Dealer has Blackjack.  You lose\n");
  }
}
