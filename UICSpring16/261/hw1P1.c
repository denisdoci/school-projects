
#include <stdio.h>

int main()
{
long long x = 0x0123456789ABCDEF;
long userInput; //number user enters
int mask = 0xF;

printf("\nGiven Number\n%llx\n\n",x);
printf("What significant nibble would you like to see: ");
scanf("%ld", &userInput);

while(userInput > 15 || userInput < 0)
{
   printf("Invalid input must be between 0 and 15\n");
   scanf("%ld", &userInput);
}
userInput = userInput << 2; 
//bit shift to is equivalent to mulitplying by 4
//this makes sense since each char in a hex is 4 bits

x = x >> (userInput);
//bit shifting the number after the desired character

x = x & mask;

//masking all the characters before desired character

printf("\nThe signifigant nibble is : %llx\n",x);

}
