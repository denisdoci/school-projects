/*
 * Denis Doci
 * CS 301
 * 663855180
 * prefix parser program
 * assumption that expression is less than 100 characters
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool eval(char ** s)
{
  if(*s[0] == 'f')
    {
         printf("f");
         return false;
    }
  else if(*s[0] == 't')
    {
         printf("t");
         return true;
    }
  else if(*s[0] == '|'){
        printf("(");
        (*s)++;
        bool first = eval(s);
        printf("|");
        (*s)++;
        bool second = eval(s);
        printf(")");
        return (first || second);
  }
  else if(*s[0] == '&'){
        printf("(");
        (*s)++;
        bool first = eval(s);
        printf("&");
        (*s)++;
        bool second = eval(s);
        printf(")");
        return (first && second);
  }
  else if(*s[0] == '!'){

        printf("!");
        (*s)++;
        bool first = eval(s);
        return !first;
  }
  else{
        printf("Expression invalid program ending.\n");
        exit(0);
  }
}

int main()
{
  char *s = malloc(sizeof(char) * 100);
  char *freeme = s;
  printf("\nThe following symbols are valid: f,t, |, &, !\n");
  printf("Enter a prefix expression with no spaces and I will transform to infix: ");

 fgets(s, sizeof s , stdin);

  
  bool result = eval(&s);

//  printf("\nBefore results");

  if(result){ printf("\nExpression is true.\n");}
  else{ printf("\nExpression is false.\n");}
  
  free(freeme);
}

