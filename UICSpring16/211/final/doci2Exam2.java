import java.io.*;
import java.util.*;

/*
 * I originally used a bubble sort but it was to slow for the 44 word file
 * so i switched it into a merge sort
 *
 */

public class doci2Exam2{
	public static void main(String[] args){

	String filename = "  "; //intitialized 

	if(args.length < 1 || args.length > 1){ //invalid input basically
		System.out.println("Filename not found in command line please enter one");
		try{
	    BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); //read in userinput
	    filename = br.readLine();
		}
		catch (IOException ioe)
		{
			System.out.println ("Couldn't understand filename provided");
		}
	}
	else{
		filename = args[0]; //otherwise its the filename provided
	}

	//this code is jacked from the notes credit: Prof. Troy
	Scanner sc;
    try{
      sc = new Scanner (new File (filename));
    }
    catch (Exception e)
    {
      System.out.println ("File " + filename + " does not exist.");
      return;
    }

	System.out.println("Filename is " + filename);

	int arraySize = 0; //size of words array
	arraySize = sc.nextInt(); //first value is the amount of words

	MyWord[] words = new MyWord[arraySize]; //array of linked lists

	System.out.println("Number of words is: " + arraySize+ "\n"); 
	System.out.println("Unsorted words are:\n");

	for(int i=0; i < arraySize; i++){ //add Char by Char each new word into a linked list
		words[i] = new MyWord(); //new linked list 
		String input = sc.next();
		for(int  j = 0; j<input.length(); j++){
			words[i].addChar(input.charAt(j));
		}
	}

	for(int i=0; i < arraySize; i++){ //printout unsorted array
		words[i].printout();
	}

	//sort(words, arraySize); //originally sort (took too long)
	mergeSort(words, arraySize); //replaced it for a merge sort

	System.out.println("\nNow sorted\n");

		for(int i=0; i < arraySize; i++){
		words[i].printout(); //print sorted array 
	}

	}

	//disregard this function ... I didnt end up using it. 
	public static void sort (MyWord[] words, int arraySize){
     int j;
     boolean flag = true;   // set flag to true to begin first pass
     MyWord temp;   //holding variable

     while ( flag )
     {
            flag= false;    //set flag to false awaiting a possible swap
            for( j=0;  j < arraySize-1;  j++ )
            {
                   if ( words[ j ].compareTo(words[j+1]) < 1 )   // change to > for ascending sort
                   {
                           temp = words[ j ];                //swap elements
                           words[ j ] = words[ j+1 ];
                           words[ j+1 ] = temp;
                           flag = true;              //shows a swap occurred  
                  } 
            } 
      } 
	}


	//i used this merge sort
	public static void mergeSort(MyWord [ ] a, int arraySize)
	{
		MyWord[] tmp = new MyWord[arraySize];
		msort(a, tmp,  0,  arraySize - 1);
	}


	private static void msort(MyWord [ ] a, MyWord [ ] tmp, int left, int right)
	{
		if( left < right )
		{
			int center = (left + right) / 2;
			msort(a, tmp, left, center);
			msort(a, tmp, center + 1, right);
			merge(a, tmp, left, center + 1, right);
		}
	}


    private static void merge(MyWord[ ] a, MyWord[ ] tmp, int left, int right, int rightEnd )
    {
        int leftEnd = right - 1;
        int k = left;
        int num = rightEnd - left + 1;

        while(left <= leftEnd && right <= rightEnd)
            if(a[left].compareTo(a[right]) <= 0) // use of the compareTo function 
                tmp[k++] = a[left++];
            else
                tmp[k++] = a[right++];

        while(left <= leftEnd)    // Copy rest of first half
            tmp[k++] = a[left++];

        while(right <= rightEnd)  // Copy rest of right half
            tmp[k++] = a[right++];

        // Copy tmp back
        for(int i = 0; i < num; i++, rightEnd--)
            a[rightEnd] = tmp[rightEnd];
    }
}