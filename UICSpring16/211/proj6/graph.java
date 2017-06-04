/*
 * Denis Doci
 * doci2
 * UIN: 663855180
 * 
 * Graph class - array of linked lists or "adjacency" list
 * 
 * I used a similar linked list class to the one I created in project 5 for my linked
 * list implementation in the Airport class. The main difference is that it is not
 * a stack, but is instead a queue. 
 *  
 * 
 */


import java.util.Iterator;
import java.util.NoSuchElementException;
public class graph{
    
	int n;  //size
	private LinkList<Integer>[] ports; //array of linked lists

	public graph(){
		n = 10;  //initialize to 10
		ports = new LinkList[10]; //set up linked lists
		for(int i=0; i<n; i++){
			ports[i] = new LinkList<Integer>();
			ports[i].push(i+1); //top
		}
	}

	public void resize(int newn){ //freeing done by java
		n = newn; //basically you can just make a new one
		ports = new LinkList[n];
		for(int i=0; i<n; i++){
			ports[i] = new LinkList<Integer>();
			ports[i].push(i+1);
		}
	}
	public void depthFirstSearchHelper (int x, int y)  //algorithim obtained project write up
	{
		for(int i=0; i<n; i++){
			ports[i].makefalse(); //make every boolean false

		}
		if ( dfs (x, y) == true)
			System.out.println("You can get from airport " + x + " to airport " + y + " in one or more flights");
		else
			System.out.println("You can NOT get from airport " + x + " to airport " + y + " in one or more flights");
	}
	boolean dfs (int a, int b)
	{
		LinkList<Integer>.Node ptr;
		for (ptr = ports[a-1].top.next; ptr!= null; ptr = ptr.next)  //traverse list
		{
			if (ptr.Obj == b)
				return true;
			if ( ptr.visited == false )
			{
				ptr.visited = true;
				if ( dfs (ptr.Obj, b) == true )
					return true;
			}
		}
		return false;
	}
	public void show(){ //print out array of linked lists
		int i;
		for(i=0; i < n; i++){
			System.out.print("Aiport[" + ports[i].top.Obj + "]:" );
			ports[i].print();
			System.out.print("\n" );
		}
	}
	public void insert(int from, int to){ //create new edge
		if(ports[from-1].contains(to)) //-1 to account for array starting at 0 not 1
			return;
		ports[from-1].push(to);
	}
	public void delete(int from, int to){ //remove edge
		ports[from-1].pop(to);
	}
	private class LinkList<Obj> implements Iterable<Obj> {
		private Node top;     // top of stack

		// helper linked list class
		private class Node {
			private Obj Obj;
			private boolean visited;
			private Node next;
		}

		// Initialize
		private LinkList() {
			top = null;
		}

		//check if empty
		private boolean isEmpty() {
			return top == null;
		}

		private void makefalse(){
			Node n = top.next;
			while(n != null){
				n.visited = false;
				n =  n.next;
			}
		}
		private void print(){
			Node n = top.next;
			while(n != null){
				System.out.print(n.Obj + " ");
				//if(n.visited == true) System.out.println(" true");
				//else System.out.println(" false");
				n = n.next;
			}
		}

		private boolean contains(Obj val){
			Node ptr = top.next;
			while(ptr != null){
				if(ptr.Obj == val){ return true;}
				ptr = ptr.next;
			}
			return false;
		}


		/*
		 * Removes and returns the Obj on top of the stack
		 */
		private void pop(Obj Obj) {
			if (isEmpty()){ 
				System.out.print("Cannot pop element: as it doesn't exist in list");
			}
			else{
				Node help = new Node(); 
				help.next= top;
				Node ptr = help;
				while(ptr.next != null){
					if(ptr.next.Obj == Obj){//find element
						Node next = ptr.next; //pop said element
						ptr.next = next.next; 
						return;
					}
					else{
						ptr = ptr.next;
					}
				}
			}
			System.out.print("Value not found on this list");
		}

		private void push(Obj Obj) { //push to back unlike on my old one where it was a stack this one is a queue
			if(top == null){
				top = new Node();
				top.Obj = Obj; 
				top.next = null;
			}
			else{
				Node newnde = top;
				while(newnde.next != null){
					newnde = newnde.next;
				}
				newnde.next = new Node();
				newnde.next.next = null;
				newnde.next.Obj = Obj;
			}
		}

		/*
		 */
		public Iterator<Obj> iterator()  { 
			return new LstItr();  
		}

		private class LstItr implements Iterator<Obj> {
			private Node curr = top;
			public boolean hasNext()  {
				return curr != null;
			}
			public void remove() { 
				throw new UnsupportedOperationException();  
			}
			public Obj next() {
				if (!hasNext()) throw new NoSuchElementException();
				Obj Obj = curr.Obj;
				curr = curr.next; 
				return Obj;
			}
		}
	}

}

