
/**
 * This file contains the User Interface code for the Infix Evaluation 
 * Project, Project 5 for CS 211 for Spring 2016.
 * 
 * Date: 3/10/16
 * 
 * @Author - Pat Troy, UIC, CS Department
 * 
 */

import java.io.*;
import java.util.*;

public class Doci2Proj5
{
  public static int debugMode = 0;
  public static void main (String[] args)
  {  

    Token inputToken;
    TokenReader tr = new TokenReader();
    String dbgM = "-d";
    System.out.print ("Starting Expression Evaluation Program\n\n");
    System.out.print ("Enter Expression: ");
    
    for(int i=0; i<args.length; i++){
    	if(args[i].compareTo(dbgM) == 0) debugMode = 1;
    	//System.out.println(args[i] + " "); errorcheck 
    }
    if(debugMode == 1){
	System.out.print("\nDebugMode is activated!\n");
    }
    inputToken = tr.getNextToken ();
    
    while (inputToken.equalsType(TokenType.QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(TokenType.HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(TokenType.ERROR))
      {
       System.out.print ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(TokenType.EOLN))
      {
       System.out.print ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else 
      {
       processExpression(inputToken, tr);
      } 

      System.out.print ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  System.out.print ("Quitting Program\n");
  return;
  
  }
  
public static void processExpression (Token inputToken, TokenReader tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
	LinkList<Integer> val = new LinkList<Integer>();
	LinkList<Character> op = new LinkList<Character>();
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(TokenType.EOLN) == false)
   {
    /* The expression contains an OPERATOR */
    if (inputToken.equalsType(TokenType.OPERATOR))
      {
       /* make this a debugMode statement */
       if(debugMode == 1){
       System.out.print ("OP: " + inputToken.getOperator() + ", ");
        }
       if(inputToken.getOperator() == '('){
    	   op.push(inputToken.getOperator());
		  // System.out.print("ha\n" + op.top() + "\n"); errorcheck
       }
       if(inputToken.getOperator() == '+' ||
    		   inputToken.getOperator() == '-'){
    	   while(!op.isEmpty() && (op.top() == '+'
    			   || op.top() == '-' || op.top() == '/'
    			   || op.top() == '*')){
    		   popAndEval(op, val);
    	   }
    	   op.push(inputToken.getOperator());
    	  // System.out.print("ha\n" + op.top() + "\n"); errorcheck
       }
       if(inputToken.getOperator() == '*' ||
    		   inputToken.getOperator() == '/'){
    	   while(!op.isEmpty() && (op.top() == '/'
    			   || op.top() == '*')){
    		    popAndEval(op, val);
    	   }
    	  op.push(inputToken.getOperator());
         // System.out.print("ha\n" + op.top() + "\n"); errorcheck
    	   
       }
       if(inputToken.getOperator() == ')'){
    	   while(!op.isEmpty() &&
    			   op.top() != '('){
    		   popAndEval(op, val);
    	   }
    	   if(op.isEmpty()){
    	     System.out.print("\nError Operator Stack is empty\n");
    	   }
    	   else{
    	     op.pop();
            // System.out.print("ha\n" + op.top() + "\n"); errorcheck 
    	     //DO NOT UNCOMMENT above it will cause stack underflow
    	   }
       }
       // add code to perform this operation here
      }
    /* The expression contain a VALUE */
    else if (inputToken.equalsType(TokenType.VALUE))
      {
       /* make this a debugMode statement */
    	if(debugMode == 1){
       System.out.print ("Val: " + inputToken.getValue() + ", "); 
    	}
       val.push(inputToken.getValue());
     //  System.out.print( val.top() + "\n"); //errorcheck
       // add code to perform this operation here

      }
   
    /* get next token from input */
    inputToken = tr.getNextToken ();
   }
 while(!op.isEmpty()){
	 popAndEval(op, val);
 }
  System.out.print("\nResult of operations: " + val.top() + "\n");
  val.pop();
  if(val.isEmpty()){
	System.out.print("\nDone\n");	
  }
  else{
	System.out.print("\nError: Value Stack is not empty\n");	
  }
 /* The expression has reached its end */

 // add code to perform this operation here

   System.out.print ("\n");
  }


/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

//popAndEval function basically obtained from 
//the write up 
private static void popAndEval(LinkList<Character> op, LinkList<Integer> val)
{
  int v1, v2, v3;
  char oper;
  oper = op.top();
  op.pop();
  v2 = val.top();
  val.pop();
  v1 =  val.top();
  val.pop();
  v3 = eval ( v1, oper, v2 );
  val.push(v3);
}

//basically just complete the operation provided
public static int eval(int v1, char op , int v2)
{
	int ret = 0;
	if(op == '+')
		ret = v1 + v2;
	else if(op == '-')
		ret = v1 - v2;
	else if(op == '*')
		ret = v1 * v2;
	else if (op == '/'){
		if(v2==0){
			System.out.print("\nError: Attempting to divide by 0");
			return -9999;
		}
		ret = v1 / v2;
	}
	return ret;
}
public static void printCommands()
{
 System.out.print ("The commands for this program are:\n\n");
 System.out.print ("q - to quit the program\n");
 System.out.print ("? - to list the accepted commands\n");
 System.out.print ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

}

class TokenReader
{
  private BufferedReader br;
  private String inline;
  private boolean needline;
  private int pos;
  
  // initialize the TokenReader class to read from Standard Input
  public TokenReader()
  {
    // set to read from Standard Input
    br = new BufferedReader (new InputStreamReader (
        System.in));
    inline = "";
    pos = 0;
    needline = true;
  }
  
  // Force the next getNextToken to read in a line of input
  public void clearToEoln()
  {
    needline = true;
  }
  
  // Return the next Token from the input line
  public Token getNextToken()
  {
    // get a new line of input from user
    if (needline)
    {
      try{
        inline = br.readLine();
      }
      catch (IOException ioe)
      {
        System.out.println ("Error in reading");
        return new Token (TokenType.EOF);
      }
      if (inline == null)
      { // End of File Encountered - Should never be the case when reading 
        //   from standard input: System.in
        return new Token (TokenType.EOF);
      }
      
      inline = inline + " ";    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }
    
    // skip over any white space characters in the beginning of the input
    while ( pos < inline.length() && 
            Character.isWhitespace(inline.charAt(pos)))
    {
      pos++;
    }
    
    // check for the end of the current line of input
    if (pos >= inline.length())
    {  // at end of line
      needline = true;
      return new Token (TokenType.EOLN);
    }
      
    // Get the next character from the input line
    char ch = inline.charAt(pos); pos++;
    
    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return new Token (TokenType.QUIT);
    }
    
    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return new Token (TokenType.HELP);
    }
    
    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t = new Token();
      t.setToOperator( ch );
      return t;
    }
     
    // check for a number  ==> VALUE Token
    if (Character.isDigit(ch))
    {
      int number = Character.digit(ch, 10);
      ch = inline.charAt(pos); pos++;
      while (Character.isDigit(ch))
      {
        number = number * 10 + Character.digit(ch, 10);
        ch = inline.charAt(pos); pos++;
      }
      pos--; // since number calculation check one character after the last digit
      Token t = new Token();
      t.setToValue( number );
      return t; 
    }
   
    // Input in not valid if code get to this part ==> ERROR Token
    return new Token (TokenType.ERROR);
  }
    
}
  
// Enumerated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOF
}

// Class to hold the Token information
class Token
{
  private TokenType type;
  private char      op;       // using '$' as undefined/error
  private int       val;      // using -999 as undefined/error
  
  // Default to initialize to the ERROR TokenType
  public Token()
  {
    type = TokenType.ERROR;
    op = '$'; 
    val = -999;
  }
  
  // Initialize to a specific TokenType
  public Token (TokenType t)
  {
    type = t;
    op = '$'; 
    val = -999;
  }
  
  // Set to a specific TokenType
  public void setToType(TokenType t)
  {
    type = t;
    op = '$'; 
    val = -999;
  }
  
  // Set to a OPERATOR TokenType with specific operator value
  public void setToOperator(char c)
  {
    type = TokenType.OPERATOR;
    op = c; 
    val = -999;
  }
  
  // Set to a VALUE TokenType with a specific numeric value
  public void setToValue(int v)
  {
    type = TokenType.VALUE;
    op = '$'; 
    val = v;
  }
  
  // return true if the Current Token is of the given TokenType
  public boolean equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }
  
  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  public boolean equalsOperator(char c)
  {
    if (type == TokenType.OPERATOR && op == c)
      return true;
    else
      return false;
  }
  
  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  public char getOperator ()
  {
    if (type == TokenType.OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }
  
  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  public int getValue()
  {
    if (type == TokenType.VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }
}
