public class MyWord{
	//node
	private Node top;

	private class Node{
		private char val;
		private Node next;
	}

	//constructor 
	public MyWord(){
		top = null;
	}

	//basically push to back
	public void addChar(char ch){
		Node nde = new Node();
		nde.val = ch;
		nde.next = null;

		if(top == null){
			top = nde;
		}
		else{
			Node tmp = top;
			while(tmp.next != null){
				tmp = tmp.next;
			}
			tmp.next = nde;
		}
	}

	//printout the list
	public void printout(){
		Node nde = top;
		while(nde!= null){
			System.out.print(nde.val);
			nde = nde.next;
		}
		System.out.print("\n");
	}

	//comparison function 
	int compareTo(MyWord w){
		Node curr = top; //set to top of given list
		Node other = w.top; //top of passed list
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
			curr= curr.next; //increment
			other= other.next;//increment
		}
		return 0;
	}
}