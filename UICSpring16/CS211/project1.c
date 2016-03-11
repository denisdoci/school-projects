#include <stdio.h>
#include <stdlib.h>

int* grow(int* darray, int *size)
{
    int* temp;
    
    temp = (int*) malloc(*size * 2 * sizeof(int) );
    int i;
    for (i = 0; i < *size; i++)
        temp[i] = darray[i];
    free(darray);
    darray = temp;
    *size = (*size * 2);
    
    return darray;
    
}

void copy(int * array1, int * array2, int count)
{
  int j;

  for(j=0; j<count; j++){
	array2[j] = array1[j];
  }
  return;
}

void sort(int * array2, int count)
{
   int j,i, temp;

   for(i = 0; i<count; ++i){
     for(j = i+1; j<count; ++j)
	{
	 if(array2[i] > array2[j])
	 {
	   temp = array2[i];
	   array2[i] = array2[j];
	   array2[j] = temp;
	 }
	}
   }
}

int linearSearch(int * array1, int searched, int *comps, int count)
{
  int c;
   for (c = 0; c < count; c++)
   {
      if (array1[c] == searched)     /* if required element found */
      {
         return c;
	 break;
      }
  (*comps)++;
   }

      return -1;
}

int binarySearch(int * array2, int searched, int *comps, int count)
{
   int first = 0;
   int last = (count-1);
   int middle = (first+last)/2;

   while(first <= last)
   {
	if(array2[middle] < searched){
	  first = middle + 1;
	  (*comps)++; 
	}
	else if(array2[middle] == searched){
	  return middle;
	  break;
	}
	else{
	  last = middle - 1;
	  (*comps)++;
	}
 	middle = (first+last)/2;
   }
  return -1;
}
int main(){

   int input, i, searched;
   int comps = 0;
   int *array1;
   int *array2;
   int count = 0;
   int size = 100;
   int pos = 0;
   int foundlin;
   int foundbin; 

   array1 = (int*) malloc(sizeof(int) *size);
   
   printf("\nEnter numbers for the array and enter -999 to quit:  ");
   scanf(" %d", &input);
   if(input == -999)
 	return 0;
   while(input!= -999)
   {
      if(count >= size){
	array1 = grow(array1, &size);
        }
	array1[count] = input;
	count++;
	scanf(" %d", &input);

   }
   array2 = (int*) malloc (sizeof(int) *count);
   copy(array1, array2, count);
   sort(array2, count);
 
   printf("\nEnter number to search for a value then -999 to quit:\n");
   scanf("%d", &searched);

   while(searched != -999)
   {  
           comps = 0; 
      foundlin = linearSearch(array1, searched, &comps, count);
      if(foundlin == -1){
	printf("\n %d is not found in the array after %d comparisons", searched, comps);
      }
      else{
	printf("\n %d was found at position %d after %d comparisons", searched, foundlin+1, comps); 
      }
     comps = 0;
     foundbin = binarySearch(array2, searched, &comps, count);
     if(foundbin == -1){
        printf("\n %d is not found in the array after %d comparisons", searched, comps);
      }
      else{
        printf("\n %d was found at position %d after %d comparisons", searched, foundbin+1, comps);
      }

 
     printf("\nEnter number to search for a value then -999 to quit:\n");
     scanf("%d", &searched);    
   }
}
