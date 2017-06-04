

/**
 * This file contains the Stack code for the Infix Evaluation  //
 * Project, Project 5 for CS 211 for Spring 2016.			  //
 * 															 //
 * Date: 3/27/16											//
 * 														   //
 * @Author - Denis Doci, UIC Student					  //
 * 														 //
 * 														//
 *---------------- IMPORTANT NOTE!!!!------------------//
 * 
 * Found code that implements Iterable<Obj> which makes it 
 * possible for the linked list to be any type and not 
 * just char or int. The code itself was found on 
 * Stack Overflow 
 * 
 * 
 */
package project5;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class LinkList<Obj> implements Iterable<Obj> {
    public Node top;     // top of stack

    // helper linked list class
    public class Node {
        private Obj Obj;
        private Node next;
    }

    // Initialize
    public LinkList() {
        top = null;
    }
    
    //check if empty
    public boolean isEmpty() {
        return top == null;
    }


    
    /*
     * Returns (but does not remove) the top Obj of the stack.
     */
    public Obj top() {
       if (isEmpty()) throw new NoSuchElementException("Nothing to top at\n");
        return top.Obj;
    }

    /*
     * Removes and returns the Obj on top of the stack
     */
    public Obj pop() {
        if (isEmpty()) throw new NoSuchElementException("Stack underflow"); //nothing to pop
        Obj Obj = top.Obj;       // save
        top = top.next;            // pop top node
        return Obj;               // return the saved Obj
    }

    public void push(Obj Obj) {
        Node oldtop = top;
        top = new Node();
        top.Obj = Obj;
        top.next = oldtop;
    }
  
    /*
     * Returns an iterator to this stack that iterates through the Objs in LIFO order.
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
    


  

