public class Sorts{
		public static void main(String[] args){
			String sortme = " asfasg";
			String sortme2 = " cdsa";
			String sortme3 = " werweq";
			String [] words = new String[3];
			words[0]= sortme;
			words[1]= sortme2;
			words[2]= sortme3;
			for(int i=0; i<3; i++){
				System.out.println(words[i]);
			}
							System.out.println("sorted");
			sort(words, 3);
			for(int i=0; i<3; i++){
				System.out.println(words[i]);
			}


}
		public static void sort (String[] words, int arraySize){
     int j;
     boolean flag = true;   // set flag to true to begin first pass
     String temp;   //holding variable

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
	/*
	int compareTo(String s, String w){
		char curr = s; //set to top of given list
		char other = w[0]; //top of passed list
		while(curr != null || other != null){ //until both are over AKA equivalent 
			if(curr == null && other!= null){
				return -1; //smaller (it reached the end)
			}
			if(curr != null && other == null){
				return 1; //bigger (the other reached the end)
			}
			if(curr.val < other.val){
				return -1; //smaller in value
			}
			if(curr.val > other.val){
				return 1;//bigger in value
			}
			curr++; //increment
			other++;//increment
		}
		return 0;
	}
	*/
		public static void mergeSort(String [ ] a, int arraySize)
	{
		String[]tmp = new String[arraySize];
		msort(a, tmp,  0,  arraySize - 1);
	}


	private static void msort(String [ ] a, String [ ] tmp, int left, int right)
	{
		if( left < right )
		{
			int center = (left + right) / 2;
			msort(a, tmp, left, center);
			msort(a, tmp, center + 1, right);
			merge(a, tmp, left, center + 1, right);
		}
	}


    private static void merge(String[ ] a, String[ ] tmp, int left, int right, int rightEnd )
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