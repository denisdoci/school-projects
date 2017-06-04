package edu.uic.denisdoci.doci2proj4;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;





public class MainActivity extends AppCompatActivity {

    /*
     * Game Notes:
     * Sometimes it can be slow but should work perfect up to specs.
     *
     * Player one starts the game he is red.
     * Player two follows until each have three pieces on board.
     *
     * Players move pieces that are on board with different AI
     * constraints, to be explained later.
     *
     * Keep going until winner is found.
     * Can win three in a row horizontally or vertically
     *
     * Start button starts the game but also restarts after game is
     * over or durring game
     */


    //for logging
    private static final String TAG = "MainActivity";

    //check if game is over
    private boolean isgameover = false;
    //counting pieces on board
    int playeronepieces = 0;
    int playertwopieces = 0;
    //we will be using this as our actual board logic
    public int[] gameBoardArray = {0,0,0,0,0,0,0,0,0};
    //display info
    private TextView gameinfo;
    //player threads
    private Thread p1Th;
    private Thread p2Th;
    //handlers for each of those threads
    public Handler handlep1;
    public Handler handlep2;
    //gridview that serves as the user ui for the game
    private GridView gridview;


    /*
      Case mapping for later
      0 = current player update info
      1 = player 1
      2 = player 2
      3 = player one thread 3 options on the board
      4 = player two thread 3 options on the board
      5 = gameover
      6 = player one thread less than 3 pieces on board
      6 = player two thread less than 3 pieces on board
     */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        //initialize threads
        p1Th = new Thread(new p1runner());
        p2Th = new Thread(new p2runner());
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // set views
        gameinfo = (TextView) findViewById(R.id.player);
        gridview = (GridView) findViewById(R.id.gridview);

        gridview.setAdapter(new ImageAdapter(this));
        //3x3 game board
        gridview.setNumColumns(3);
    }

    public void setHandlersNull()
    {
        //reset all the handlers and remove
        //their callbacks and messages
        handlep1.removeCallbacksAndMessages(null);
        handlep2.removeCallbacksAndMessages(null);
        userinterfaceHandler.removeCallbacksAndMessages(null);
    }
    public void startgame(View v)
    {
        //boolean checks to see if threads are alive
        boolean p1 = p1Th.isAlive();
        boolean p2 = p2Th.isAlive();

        //check if it is game over
        if(isgameover){
            //setHandlersNull();
            try{
                // join threads
                p1Th.join();
                p2Th.join();
            }
            catch (Exception ex)
            {
                Log.i(TAG, "Issue in the join of start game ");
            }
            //reinitialize game
            initGame();
            //restart the threads
            p1Th = new Thread(new p1runner());
            p1Th.start();
            p2Th = new Thread(new p2runner());
            p2Th.start();
            //reset game over
            isgameover = false;
        }

        //game is not over
        else {
            //p1 is not alive
            if (!p1) {
                //restart player 1
                p1Th = new Thread(new p1runner());
                p1Th.start();
            }
            else {
                //player1 is alive
                //initialize game remove all handlers/messages
                //restart p1
                initGame();
                setHandlersNull();
                p1Th = new Thread(new p1runner());
                p1Th.start();
            }
            //p2 isnt alive
            if (!p2) {
                //restart p2
                p2Th = new Thread(new p2runner());
                p2Th.start();

            }
            else {
                //player2 is alive
                //initialize game remove all handlers/messages
                //restart p2
                initGame();
                setHandlersNull();
                p2Th = new Thread(new p2runner());
                p2Th.start();
            }

        }
    }

    /*
     * Before game official begins
     * get the player 1 thread to make an
     * initial move just to set things off
     */
    void initialstep()
    {
        String val = "Player 1";
        //get a random variable
        int index = getfreerandom();
        //send player one info to userinterface handler
        Message message = userinterfaceHandler.obtainMessage(0);
        message.obj = val;
        userinterfaceHandler.sendMessage(message);

        //set that random index to 1 so it is initialized for player one
        gameBoardArray[index] = 1;

        //send userinterface information about change of board
        Message message1 = userinterfaceHandler.obtainMessage(1);
        message1.arg1 = index;
        message1.arg2 = 1;
        userinterfaceHandler.sendMessage(message1);
    }


    //this is the class that runs the player 1 thread
    //almost identical to the player 2 thread class they serve much of the same
    //purpose
    public class p1runner implements Runnable{

        public void run(){

            Looper.prepare();
            final String player1 = "Player 1";
            //launch game
            initialstep();

            //handler for the runner
            handlep1 = new Handler(){
                //messages we need to send to the UI
                Message firstuimessage;
                Message seconduimessage;
                public void handleMessage(Message message)
                {
                    //comments walk through simple AI implementation
                    int messageval = message.what;

                    switch(messageval){
                        case 6:{
                            //not enough player one pieces
                            firstuimessage = userinterfaceHandler.obtainMessage(0);
                            firstuimessage.obj = player1;
                            userinterfaceHandler.sendMessage(firstuimessage);
                            //get a random index
                            int currentIndex = getfreerandom();
                            //set that index for player one
                            gameBoardArray[currentIndex] = 1;
                            //notify UI
                            seconduimessage = userinterfaceHandler.obtainMessage(1);
                            seconduimessage.arg1 = currentIndex;
                            seconduimessage.arg2 = 1;

                            userinterfaceHandler.sendMessage(seconduimessage);
                            break;
                        }
                        //in this case we have all of our player one pieces down
                        case 3:{
                            //notify ui of player one
                            firstuimessage = userinterfaceHandler.obtainMessage(0);
                            firstuimessage.obj = player1;
                            userinterfaceHandler.sendMessage(firstuimessage);
                            //this function returns a random free space
                            //and chooses a random player one piece on the
                            // board to send to that space
                            int currentIndex = moverandomavailable();
                            gameBoardArray[currentIndex] = 1;
                            //notify ui
                            seconduimessage = userinterfaceHandler.obtainMessage(1);
                            seconduimessage.arg1 = currentIndex;
                            seconduimessage.arg2 = 1;
                            userinterfaceHandler.sendMessage(seconduimessage);
                            break;
                        }

                        case 5:{
                            //game over quit the looper
                            handlep1.getLooper().quit();
                            break;
                        }
                    }
                }
            };
            Looper.loop();
        }
    }

    //handler for the user interface
    //communicates between both threads of players
    //updates board

    private Handler userinterfaceHandler = new Handler(){
        public void handleMessage(Message msg){
            int messageval = msg.what;
            //keep track of board pieces
            playeronepieces = 0;
            playertwopieces = 0;
            String gameStatus = "";

            //update board piece numbers
            for(int i= 0; i<9; i++)
            {
                if(gameBoardArray[i]==1) playeronepieces++;
                if(gameBoardArray[i]==2) playertwopieces++;

            }
            switch(messageval){
                //update textview info
                case 0:{
                    String currPlayer = (String)msg.obj;
                    gameinfo.setText(currPlayer);
                    if(currPlayer.equals("Player 1"))
                    {
                        gameinfo.setBackgroundColor(Color.RED);
                        gameinfo.setTextColor(Color.BLACK);
                    }
                    if(currPlayer.equals("Player 2"))
                    {
                        gameinfo.setBackgroundColor(Color.BLACK);
                        gameinfo.setTextColor(Color.RED);                    }
                    break;
                }
                //dealing with thread one
                case 1:
                {
                    //index
                    int ind = (int)msg.arg1;
                    //thread one
                    int playerNum = (int)msg.arg2;

                    //update board
                    updtBoard(ind, playerNum);
                    //check if anyone one
                    gameStatus = checkwin(ind, playerNum);
                    //if no one one
                    if(gameStatus.equals("Continue"))
                    {
                        //pause for a second
                        try {
                            p1Th.sleep(1000);
                        }
                        catch (InterruptedException e)
                        {
                            Log.i(TAG, "Thread sleep issue");
                        };
                        //check if player 2 has enough pieces
                        if(playertwopieces < 3)
                        {
                            //do player 2 with less than 3 so it can add
                            Message msg1 = handlep2.obtainMessage(7);
                            handlep2.sendMessage(msg1);
                        }
                        else
                        {
                            //do player 2 with more than 3 so it can move pieces
                            Message msg1 = handlep2.obtainMessage(4);
                            handlep2.sendMessage(msg1);
                        }
                        //sleep
                        try {
                            Thread.sleep(1000);
                        }
                        catch (InterruptedException e)
                        {
                            Log.i(TAG, "Thread sleep issue");
                        }
                        break;
                    }
                    else
                    {
                        //game over

                        Message msg1 = handlep1.obtainMessage(5);
                        handlep1.sendMessage(msg1);

                        //reset all the variables
                        isgameover = true;
                        playeronepieces = 0;
                        playertwopieces = 0;

                        Message msg2 = handlep2.obtainMessage(5);
                        handlep2.sendMessage(msg2);
                        gameinfo.setText("Game Over P1 wins!");

                        try { Thread.sleep(1000); }
                        catch (InterruptedException e) {
                            Log.i(TAG, "Thread sleep issue");
                        };
                    }

                    break;
                }
                case 2:
                {
                    //index
                    int ind = (int) msg.arg1;
                    //player2
                    int playerNum = (int) msg.arg2;
                    //update board
                    updtBoard(ind, playerNum);
                    //check for winner
                    gameStatus = checkwin(ind, playerNum);
                    //no winner
                    if (gameStatus.equals("Continue"))
                    {
                        //sleep
                        try {
                            p2Th.sleep(1000);
                        }
                        catch (InterruptedException e)
                        {
                            Log.i(TAG, "Thread sleep issue");
                        }
                        ;
                        //check for player one pieces
                        if (playeronepieces < 3)
                        {
                            //not enough lets add
                            Message msg1 = handlep1.obtainMessage(6);
                            handlep1.sendMessage(msg1);
                        }
                        else {
                            //enough lets move em around
                            Message msg1 = handlep1.obtainMessage(3);
                            handlep1.sendMessage(msg1);
                        }
                        try {
                            Thread.sleep(1000);
                        }
                        catch (InterruptedException e) {
                            Log.i(TAG, "Thread sleep issue");
                        }
                        break;
                    }
                    else {
                        //game over lets reset pieces
                        isgameover = true;
                        playertwopieces = 0;
                        playeronepieces = 0;
                        //notify threads of game over
                        Message msg1 = handlep1.obtainMessage(5);
                        handlep1.sendMessage(msg1);
                        Message msg2 = handlep2.obtainMessage(5);
                        handlep2.sendMessage(msg2);
                        //update scoreboard
                        gameinfo.setText("Game Over P2 wins!");
                        try {
                            Thread.sleep(1000);
                        } catch (InterruptedException e) {
                            Log.i(TAG, "Thread sleep issue");
                        }
                        ;
                        break;
                    }
                }
            }
        }
    };

    //player 2 class almost exactly similar to player one
    //ill comment the difference in ai

    public class p2runner implements Runnable{
        String player2 = "Player 2";
        public void run(){
            Looper.prepare();

            handlep2 = new Handler(){
                Message uimessage1;
                Message uimessage2;
                public void handleMessage(Message msg)
                {
                    int messageval = msg.what;
                    switch(messageval){
                        case 7:{
                            uimessage1 = userinterfaceHandler.obtainMessage(0);
                            uimessage1.obj = player2;
                            userinterfaceHandler.sendMessage(uimessage1);

                            int currentIndex = getfreerandom();
                            gameBoardArray[currentIndex] = 2;
                            uimessage2 = userinterfaceHandler.obtainMessage(2);
                            uimessage2.arg1 = currentIndex;
                            uimessage2.arg2 = 2;
                            userinterfaceHandler.sendMessage(uimessage2);
                            break;
                        }
                        case 4:{
                            uimessage1 = userinterfaceHandler.obtainMessage(0);
                            uimessage1.obj = player2;
                            userinterfaceHandler.sendMessage(uimessage1);

                            //heres the simple ai design change
                            //instead of moving any piece on the board
                            //player two will always select its first piece
                            //and move that to an open spot
                            //works a lot  more than the other one actually
                            int currentIndex = movefirstavailable();
                            gameBoardArray[currentIndex] = 2;
                            uimessage2 = userinterfaceHandler.obtainMessage(2);
                            uimessage2.arg1 = currentIndex;
                            uimessage2.arg2 = 2;
                            userinterfaceHandler.sendMessage(uimessage2);
                            break;
                        }
                        case 5:{
                            handlep2.getLooper().quit();
                            break;
                        }
                    }
                }
            };

            Looper.loop();
        }
    }

    //in this function find all the pieces on the board
    //chose a random one
    // move that piece

    int moverandomavailable()
    {
        //this will be the new position aka what we return
        int newPos = getfreerandom();
        List<Integer> currentpos = new ArrayList<>();

        //gather the selection of board peices
        for(int i = 0; i<9; i++)
        {

            if(gameBoardArray[i] == 1) {
                currentpos.add(i);
            }
        }

        //chose one at random
        Random rand = new Random();
        int index = rand.nextInt(currentpos.size());
        int pos = currentpos.get(index);
        //reset that index to neutral
        gameBoardArray[pos] = 0;
        return newPos;
    }

    //this is for player two
    // move the first available piece to a random spot
    int movefirstavailable()
    {
        //this will be our new random spot
        int newPos = getfreerandom();

        //search for player 2 piece
        for(int i = 0; i<9; i++)
        {
            //found first one
            if(gameBoardArray[i] == 2){
                //reset that piece to neutral and break
                gameBoardArray[i] = 0;
                break;
            }
        }
        return newPos;
    }

    //find a random free space on the board
    //returns that index
    public int getfreerandom()
    {
        Random rand = new Random();
        while(true)
        {
            int r = rand.nextInt((8) + 1);
            if(gameBoardArray[r] == 0)
            {
                return r;
            }
        }

    }
    //reset all the board
    //set the game board to neutral and
    //set colors to white
    public void initGame()
    {
        for(int i = 0; i<9; i++) {
            gameBoardArray[i] = 0;
            View tv = (View)gridview.getChildAt(i);
            tv.setBackgroundColor(Color.parseColor("white"));
        }

    }

    //this is to check the win using our game board array
    //only two ways to win horizontal and vertical
    public String checkwin(int index, int thread)
    {
        String gameStatus = "Continue";

        /*
             0 1 2
             3 4 5
             6 7 8
        */

        //player one
        if(thread == 1)
        {
            if(index>=0 && index <=2){
                //first row
                if(gameBoardArray[index + 3] == 1 && gameBoardArray[index + 6] ==1 )
                {
                    //vertical win
                    gameStatus = "Win";
                }
                if(gameBoardArray[0] == 1 && gameBoardArray[1] ==1 && gameBoardArray[2] ==1){
                    //horizontal win
                    gameStatus = "Win";
                }
            }
            else if (index>=3 && index <= 5){
                //second row
                if(gameBoardArray[index + 3] == 1 && gameBoardArray[index - 3] ==1 )
                {
                    //vertical win
                    gameStatus = "Win";
                }
                if(gameBoardArray[3] == 1 && gameBoardArray[4] ==1 && gameBoardArray[5] ==1){
                    //horizontal win
                    gameStatus = "Win";
                }
            }
            else{
                //last row
                if(gameBoardArray[index - 3] == 1 && gameBoardArray[index - 6] ==1 )
                {
                    //vertical win
                    gameStatus = "Win";
                }
                if(gameBoardArray[6] == 1 && gameBoardArray[7] ==1 && gameBoardArray[8] ==1){
                    //horizontal win
                    gameStatus = "Win";
                }
            }

        }
        //player 2
        else{
            if(index>=0 && index <=2){
                //first row
                if(gameBoardArray[index + 3] == 2 && gameBoardArray[index + 6] == 2 )
                {
                    //vertical win
                    gameStatus = "Win";
                }
                if(gameBoardArray[0] == 2 && gameBoardArray[1] == 2 && gameBoardArray[2] == 2){
                    //horizontal win
                    gameStatus = "Win";
                }
            }
            else if (index>=3 && index <= 5){
                //second row
                if(gameBoardArray[index + 3] == 2 && gameBoardArray[index - 3] == 2 )
                {
                    //vertical win
                    gameStatus = "Win";
                }
                if(gameBoardArray[3] == 2 && gameBoardArray[4] == 2 && gameBoardArray[5] == 2){
                    //horizontal win
                    gameStatus = "Win";
                }
            }
            else{
                //last row
                if(gameBoardArray[index - 3] == 2 && gameBoardArray[index - 6] == 2 )
                {
                    //vertical win
                    gameStatus = "Win";
                }
                if(gameBoardArray[6] == 2 && gameBoardArray[7] == 2 && gameBoardArray[8] == 2){
                    //horizontal win
                    gameStatus = "Win";
                }
            }
        }
        return gameStatus;
    }
    //update the board colors using our game board array
    public void updtBoard(int index, int threadNumber)
    {
        for(int i = 0; i<9; i++)
        {
            //if one color is red for player one
            if(gameBoardArray[i]==1){
                View tv = (View) gridview.getChildAt(i);
                tv.setBackgroundColor(Color.RED);
            }
            //if two color is black for player two
            else if(gameBoardArray[i]==2) {
                View tv = (View) gridview.getChildAt(i);
                tv.setBackgroundColor(Color.BLACK);
            }
            //if zero color is white and neutral
            else if(gameBoardArray[i]==0)
            {
                View tv = (View)gridview.getChildAt(i);
                tv.setBackgroundColor(Color.WHITE);
            }
        }

    }
    //image adapter for the grid view this is pretty self explanitory
    //just the standard android image adapter
    private class ImageAdapter extends BaseAdapter {
        private Context mContext;

        public ImageAdapter(Context c) {
            mContext = c;
        }

        public int getCount() {
            return 9;
        }

        public Object getItem(int position) {
            return null;
        }

        public long getItemId(int position) {
            return 0;
        }

        public View getView(int position, View convertView, ViewGroup parent) {
            ImageView imageView;
            if (convertView == null) {
                imageView = new ImageView(mContext);
                imageView.setLayoutParams(new GridView.LayoutParams(300, 350));
                imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
                imageView.setPadding(20, 20, 20, 20);
                return imageView;
            } else {
                imageView = (ImageView) convertView;
            }

            //imageView.setBackgroundColor(Color.parseColor("white"));
            return imageView;
        }

    }
}
