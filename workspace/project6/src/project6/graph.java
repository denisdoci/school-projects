package project6;

/*
 * Denis Doci
 * doci2
 * UNI: 663855180
 * 
 * Airport class - array of linked lists or "adjacency" list
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
	int n;
	private LinkList<Integer>[] ports;

	public graph(){
		n = 10;
		ports = new LinkList[10];
		for(int i=0; i<n; i++){
			ports[i] = new LinkList<Integer>();
			ports[i].push(i+1);
		}
	}

	public void resize(int newn){
		n = newn;
		ports = new LinkList[n];
		for(int i=0; i<n; i++){
			ports[i] = new LinkList<Integer>();
			ports[i].push(i+1);
		}
	}
	public void depthFirstSearchHelper (int x, int y)
	{
		for(int i=0; i<n; i++){
			ports[i].makefalse();

		}
		if ( dfs (x, y) == true)
			System.out.println("You can get from airport " + x + " to airport " + y + " in one or more flights");
		else
			System.out.println("You can NOT get from airport " + x + " to airport " + y + " in one or more flights");
	}
	boolean dfs (int a, int b)
	{
		LinkList<Integer>.Node ptr;
		for (ptr = ports[a-1].top.next; ptr!= null; ptr = ptr.next)
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
	public void show(){
		int i;
		for(i=0; i < n; i++){
			System.out.print("Aiport[" + ports[i].top.Obj + "]:" );
			ports[i].print();
			System.out.print("\n" );
		}
	}
	public void insert(int from, int to){
		if(ports[from-1].contains(to)) 
			return;
		ports[from-1].push(to);
	}
	public void delete(int from, int to){
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
					if(ptr.next.Obj == Obj){
						Node next = ptr.next;
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

		private void push(Obj Obj) {
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

