package project7;

public class Ant extends animal{
	private Island isl;
	private int x;
	private int y;
	private int dayLastMoved;
	private int daysAlive=0;

	public Ant (Island island)
	{
		isl = island;
		x = (int)(Math.random() * island.getRows() );
		y = (int)(Math.random() * island.getCols() );
		dayLastMoved = 0;

		island.addAnt (this, x, y);
	}

	public void move ()
	{
		int nextX = -999;
		int nextY = -999;
		int direction = (int)(Math.random() * 4);
		if (direction == 0) // attempt to move up
		{
			nextX = x; nextY = y-1;
		}
		if (direction == 1) // attempt to move down
		{
			nextX = x; nextY = y+1;
		}
		if (direction == 2) // attempt to move left
		{
			nextX = x-1; nextY = y;
		}
		if (direction == 3) // attempt to move right
		{
			nextX = x+1; nextY = y;
		}

		//System.out.println ("Try to move from (" + x + ", " + y +") to (" + nextX + ", " + nextY + ")" );

		// try to move the beetle to the NEXT position
		if ( isl.moveAnt ( x, y, nextX, nextY ) == true)
		{
			x = nextX;
			y = nextY;
		}
	}

	public void setDayLastMoved (int dlm)
	{
		dayLastMoved = dlm;
	}

	public int getDayLastMoved ()
	{
		return dayLastMoved;
	}
	public void aliveAnotherDay(){
		daysAlive++;
	}
	public int getDaysAlive(){
		return daysAlive;
	}
	public void breed()
	{

		if ( isl.canBreed ( x, y) == true)
		{
			if(isl.isOccupied(x+1, y))
				isl.addAnt(this, x+1, y);
			else if(isl.isOccupied(x-1, y))
				isl.addAnt(this, x-1, y);
			else if(isl.isOccupied(x, y-1))
				isl.addAnt(this, x, y-1);
			else 
				isl.addAnt(this, x, y+1);
		}
	}

}
