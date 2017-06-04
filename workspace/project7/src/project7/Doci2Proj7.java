package project7;

public class Doci2Proj7
{
	public static void main (String[] args)
	{
		// create my island
		Island island = new Island();
		int sleepTime=0;

		if(args.length == 0) sleepTime = 250;

		else if(args.length == 1 || args.length > 2 ){
			System.out.println("Invalid commandline arguement");
			System.exit(0);
		}
		else{
			if(!args[0].equals("-d")){
				System.out.println("-d Flag not found");
				System.exit(0);
			}

			try {
				sleepTime = Integer.parseInt(args[1]);
			} catch (NumberFormatException e) {
				System.err.println("Argument 2 must be an integer.");
				System.exit(1);
			}
		}

		for (int i = 0 ; i < 5 ; i++)
		{
			Doodlebug b = new Doodlebug(island);
		}
		for (int i = 0 ; i < 100 ; i++){
			Ant a = new Ant(island);
		}
		// run simulation for 20 days
		for (int i = 0 ; i < 20; i++)
		{
			GridDisplay.mySleep (sleepTime);
			island.nextDayDoodlebug();
			island.nextDayAnt();
		}
	}
}

