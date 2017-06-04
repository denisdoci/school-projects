package edu.uic.denisdoci.doci2project3a3;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;


/**
 * Created by denisdoci on 3/25/17.
 */

/*
    Note much of this was taken from Prof. Ugo Buy's Example on broadcast receivers
 */

public class a3Reciever extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent arg1) {

        Context appContext = context.getApplicationContext();
        if(arg1.getAction().equals("Baseball")) {
            Intent aIntent = new Intent(context, BaseballActivity.class);
            aIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            appContext.startActivity(aIntent);
        }
        if(arg1.getAction().equals("Basketball")){
            Intent aIntent = new Intent(context, BasketballActivity.class);
            aIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            appContext.startActivity(aIntent);
        }
    }
}