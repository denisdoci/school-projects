	
import java.util.Iterator;
import java.util.NoSuchElementException;


/*
 * More or less the same LinkList ADT I turned in for project5
 * the purpose of this is to keep a LinkList of filesnames that have
 * already been used. 
 */

public class FilesInUse<Obj> implements Iterable<Obj>{

	private Node top;     // top of stack

	// helper linked list class
	private class Node {
		private Obj Obj;
		private Node next;
	}

	// Initialize
	public FilesInUse() {
		top = null;
	}

	//check if empty
	public boolean isEmpty() {
		return top == null;
	}

    //prints linked list
	public void print(){
		Node n = top;
		while(n != null){
			System.out.println("\nLists contains:"+ n.Obj + "\n");
			//if(n.visited == true) System.out.println(" true");
			//else System.out.println(" false");
			n = n.next;
		}
	}

    //boolean to check if given element is present in list
	public boolean contains(Obj Obj){
		Node ptr = top;
		while(ptr != null){
			if(ptr.Obj.equals(Obj))
			return true;
			ptr = ptr.next;
		}
		return false;
	}


	/*
	 * Pushes element onto linked list
     */


	public void push(Obj Obj) {
        Node oldtop = top;
        top = new Node();
        top.Obj = Obj;
        top.next = oldtop;
	}
    /*
     * Removes given element from linked list
     */
	public void pop(Obj Obj) {
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


