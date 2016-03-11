#include <stdio.h>
int main()
{
 long x = 0xdeadbeef;
 long result = 0;
 long mask;
 for (mask = 1; mask != 0; mask= mask<< 2) {
   result |= (mask&x);
 }      
 printf("result %lx\n",result);
 }           
/*    
Question 1:
x - %eax and then moved to 8 bits in memory before register %rbp. (-8(%rbp))

result- is stored 24 bits in memory before register %rbp. (-24(%rbp))

mask- is stored orginally at 16 bits in memory before rbp (-8(%rbp)). But then as
      the variable iterates through the loop it gets passed between registers
      %rax and %rsi. 

Question 2:

First the program declares and initializes 3 variables. x as the hex value 
0xdeadbeef, result as 0, and mask which does not need to be initialized 
as it is the iterating variable.

Then the program executes a for loop by setting mask equal to 1, and shifting 2 bits left
for every iteration until variable mask equals zero. As long is a 64 bit variable
the loop will iterate 32 times for it to equal zero. This is because the 1 is in the lsb
so to bit shift it to the gsb and then shift that to have mask equal to zero
it will take 32 times because you're shifting by 2 each time. 

Within the loop there are 2 bit operations occuring. The first is an and operation between
the mask, which is constantly changing as it is iterating, and x which is always the 
hex number 0xdeadbeef. Lets call the result of this operation y. So then "result" is set 
equal to the value of result with a bitwise or operation of y. This is done 32 times within the loop
and the variable result is then printed in hexidecimal format. 
  
*/ 
