package project6;

import java.util.Iterator;
import java.util.NoSuchElementException;



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

	public void print(){
		Node n = top.next;
		while(n != null){
			System.out.println(n.Obj + " ");
			//if(n.visited == true) System.out.println(" true");
			//else System.out.println(" false");
			n = n.next;
		}
	}

	public boolean contains(Obj Obj){
		Node ptr = top;
		while(ptr != null){
			if(ptr.Obj == Obj){ return true;}
			ptr = ptr.next;
		}
		return false;
	}


	/*
	 * Removes and returns the Obj on top of the stack
	 */


	public void push(Obj Obj) {
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


