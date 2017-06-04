package project6;
/*
 * Denis Doci
 * doci2
 * UNI: 663855180
 * 
 * base for project 6 provided by Professor Troy
 * 
 */
import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Proj6BaseV2
{

	public static void main (String[] args)
	{
		// set up an instance of the BufferedReader class to read from standard input
		BufferedReader br = new BufferedReader (new InputStreamReader (
				System.in));

		// set up the data needed for the airport adjacency list
		Proj6BaseV2 airportData = new Proj6BaseV2();

		graph airports = new graph();
		FilesInUse<String> files = new FilesInUse<String>();

		// call the method that reads and parses the input
		airportData.processCommandLoop (br, airports, files);

		System.out.println ("Goodbye");
	}


	public void processCommandLoop (BufferedReader br, graph airports, FilesInUse<String> files)
	{
		try {  //try-catch clauses are needed since BufferedReader and Scanner classes
			//  throw exceptions on errors
			String inline = br.readLine();   // get a line of input
			Scanner sc;

			// loop until all lines are read from the input
			while (inline != null)
			{
				sc = new Scanner (inline);   // process each line of input using the Scanner iterators
				String command = sc.next();
				System.out.println ("*" + command + "*");

				if (command.equals("q") == true)
					System.exit(1);

				else if (command.equals("?") == true)
					showCommands();

				else if (command.equals("t") == true)
					doTravel(sc, airports);

				else if (command.equals("r") == true)
					doResize(sc, airports);

				else if (command.equals("i") == true)
					doInsert(sc, airports);

				else if (command.equals("d") == true)
					doDelete(sc, airports);

				else if (command.equals("l") == true)
					doList(sc, airports);

				else if (command.equals("f") == true)
					doFile(sc, airports, files);

				else if (command.equals("#") == true)
					;

				else
					System.out.println ("Command is not known: " + command);

				inline = br.readLine();   // get the next line of input

			}
		}
		catch (IOException ioe)
		{
			System.out.println ("Error in Reading - Assuming End of File");
		}
	}

	public void showCommands()
	{
		System.out.println ("The commands for this project are:");
		System.out.println ("  q ");
		System.out.println ("  ? ");
		System.out.println ("  # ");
		System.out.println ("  t <int1> <int2> ");
		System.out.println ("  r <int> ");
		System.out.println ("  i <int1> <int2> ");
		System.out.println ("  d <int1> <int2> ");
		System.out.println ("  l ");
		System.out.println ("  f <filename> ");
	}

	public void doTravel(Scanner sc, graph airports)
	{
		int val1 = 0;
		int val2 = 0;

		if ( sc.hasNextInt() == true )
			val1 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		if ( sc.hasNextInt() == true )
			val2 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		System.out.println ("Performing the Travel Command from " + val1 +
				" to " + val2);
		if(val1 > airports.n || val1 <= 0 || val2 > airports.n || val2 <= 0){
			System.out.println ("\nNumbers not in range try again.");
		}
		else{
			airports.depthFirstSearchHelper(val1, val2);
		}
	}

	public void doResize(Scanner sc, graph airports)
	{
		int val1 = 0;

		if ( sc.hasNextInt() == true )
			val1 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		System.out.println ("Performing the Resize Command with " + val1 );

		airports.resize(val1);
	}

	public void doInsert(Scanner sc, graph airports)
	{
		int val1 = 0;
		int val2 = 0;

		if ( sc.hasNextInt() == true )
			val1 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		if ( sc.hasNextInt() == true )
			val2 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		System.out.println ("Performing the insert Command from airport " + val1 +
				" to " + val2);
		if(val1 > airports.n || val1 <= 0 || val2 > airports.n || val2 <= 0){
			System.out.println ("\nNumbers not in range try again.");
		}
		else{
			airports.insert(val1, val2);
		}
	}

	public void doDelete(Scanner sc, graph airports)
	{
		int val1 = 0;
		int val2 = 0;

		if ( sc.hasNextInt() == true )
			val1 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		if ( sc.hasNextInt() == true )
			val2 = sc.nextInt();
		else
		{
			System.out.println ("Integer value expected");
			return;
		}

		System.out.println ("Performing the delete command from airports " + val1 +
				" to " + val2);
		if(val1 > airports.n || val1 <= 0 || val2 > airports.n || val2 <= 0){
			System.out.println ("\nNumbers not in range try again.");
		}
		else{
			airports.delete(val1, val2);
		}
	}

	public void doList(Scanner sc, graph airports)
	{
		airports.show();

	}

	public void doFile(Scanner sc, graph airports, FilesInUse<String> files)
	{
		// next steps:  (print an error message and return if any step fails) 
		//  1. verify the file name is not currently in use
		//  2. open the file
		//  3. create a new instance of BufferedReader
		//        BufferedReader br = new BufferedReader (new FileReader ("MyFileReader.txt"));
		//  4. recursively call processCommandLoop() with this new instance of BufferedReader as the parameter
		//  5. close the file when processCommandLoop() returns

		BufferedReader br = null;
		try{
			String fname = null;

			if ( sc.hasNext() == true )
				fname = sc.next();
			else
			{
				System.out.println ("Filename expected");
				return;
			}
			if(files.contains(fname)){
				System.out.println ("File already in use");
				return;
			}
			System.out.println ("Performing the File command with file: " + fname);
			files.push(fname);

			File file = new File(fname);
			br = new BufferedReader(new FileReader(file));
			processCommandLoop(br, airports, files);
			files.pop(fname);
		}
		catch(FileNotFoundException ex){
			Logger.getLogger(Proj6BaseV2.class.getName()).log(Level.SEVERE, null, ex);
		}
		finally{
			try{
				if(br != null)
					br.close();
			}
			catch(IOException ex){
				Logger.getLogger(Proj6BaseV2.class.getName()).log(Level.SEVERE, null, ex);
			}
		}

	}

}