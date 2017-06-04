package edu.uic.denisdoci.doci2project3a3;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import edu.uic.denisdoci.doci2project3a3.BaseballTeamFragment.ListSelectionListener;


/*
    Note much of this was taken from Prof. Ugo Buy's Example on fragments
 */
public class BaseballActivity extends AppCompatActivity implements
        ListSelectionListener {

    public static String[] mTitleArray;
    public static String[] mQuoteArray;


    private final BaseballWebviewFragment mQuoteFragment = new BaseballWebviewFragment();
    private FragmentManager mFragmentManager;
    private FrameLayout mTitleFrameLayout, mQuotesFrameLayout;

    private static final int MATCH_PARENT = LinearLayout.LayoutParams.MATCH_PARENT;
    private static final String TAG = "QuoteViewerActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {


        super.onCreate(savedInstanceState);

        // Get the string arrays with the titles and qutoes
        mTitleArray = getResources().getStringArray(R.array.BaseballTeams);
        mQuoteArray = getResources().getStringArray(R.array.BaseballWebsites);

        setContentView(R.layout.main);

        mTitleFrameLayout = (FrameLayout) findViewById(R.id.title_fragment_container);
        mQuotesFrameLayout = (FrameLayout) findViewById(R.id.quote_fragment_container);


        // Get a reference to the FragmentManager
        mFragmentManager = getFragmentManager();

        // Start a new FragmentTransaction
        FragmentTransaction fragmentTransaction = mFragmentManager
                .beginTransaction();

        // Add the TitleFragment to the layout
        fragmentTransaction.replace(R.id.title_fragment_container,
                new BaseballTeamFragment());

        // Commit the FragmentTransaction
        fragmentTransaction.commit();

        // Add a OnBackStackChangedListener to reset the layout when the back stack changes
        mFragmentManager
                .addOnBackStackChangedListener(new FragmentManager.OnBackStackChangedListener() {
                    public void onBackStackChanged() {
                        setLayout();
                    }
                });
    }

    private void setLayout() {

        if(getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
            // Determine whether the QuoteFragment has been added
            if (!mQuoteFragment.isAdded()) {

                // Make the TitleFragment occupy the entire layout
                mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
                        MATCH_PARENT, MATCH_PARENT));
                mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT));
            } else {

                // Make the TitleLayout take 1/3 of the layout's width
                mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT, 1f));

                // Make the QuoteLayout take 2/3's of the layout's width
                mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT, 2f));
            }
        }
        else
        {
            // Determine whether the QuoteFragment has been added
            if (!mQuoteFragment.isAdded()) {

                // Make the TitleFragment occupy the entire layout
                mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
                        MATCH_PARENT, MATCH_PARENT));
                mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT));
            } else {

                // Make the TitleLayout take 1/3 of the layout's width
                mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
                        MATCH_PARENT));

                // Make the QuoteLayout take 2/3's of the layout's width
                mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
                        MATCH_PARENT, MATCH_PARENT));
            }
        }
    }

    @Override
    public void onStart() {
        super.onStart()  ;
        if (ContextCompat.checkSelfPermission(this, "edu.uic.cs478.project3") !=
                PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{"edu.uic.cs478.project3"}, 0);
        }
    }

    @Override
    public void onResume() {
        super.onResume();  ;
        if (ContextCompat.checkSelfPermission(this, "edu.uic.cs478.project3") !=
                PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{"edu.uic.cs478.project3"}, 0);
        }
    }
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        setLayout();
    }

    @Override
    public void onListSelection(int index) {

        // If the QuoteFragment has not been added, add it now
        if (!mQuoteFragment.isAdded()) {

            // Start a new FragmentTransaction
            FragmentTransaction fragmentTransaction = mFragmentManager
                    .beginTransaction();

            // Add the QuoteFragment to the layout
            fragmentTransaction.add(R.id.quote_fragment_container,
                    mQuoteFragment);

            // Add this FragmentTransaction to the backstack
            fragmentTransaction.addToBackStack(null);

            // Commit the FragmentTransaction
            fragmentTransaction.commit();

            // Force Android to execute the committed FragmentTransaction
            mFragmentManager.executePendingTransactions();
        }

        if (mQuoteFragment.getShownIndex() != index) {

            // Tell the QuoteFragment to show the quote string at position index
            mQuoteFragment.showQuoteAtIndex(index);
        }
    }

    //create and add items to options menu
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.toolbar_menu, menu);
        return true;
    }
    //when option is selected check which one was clicked
    //depending on that go to corresponding file
    @Override
    public boolean onOptionsItemSelected( MenuItem item) {
        int id = item.getItemId();
        switch (id) {
            case R.id.baseball:
                //do nothing we're already in this activity
                return true;
            case R.id.basketball:
                Intent aIntent = new Intent(this, BasketballActivity.class);
                aIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(aIntent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

}