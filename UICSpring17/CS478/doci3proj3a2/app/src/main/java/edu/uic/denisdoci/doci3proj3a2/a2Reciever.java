package edu.uic.denisdoci.doci3proj3a2;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/**
 * Created by denisdoci on 3/25/17.
 */

public class a2Reciever extends BroadcastReceiver {
    @Override
    public void onReceive(Context arg0, Intent arg1) {
        //action is baseball button
        if(arg1.getAction().equals("Baseball")) {
            Toast.makeText(arg0, "A2 Receiver: Baseball was the chosen sport",
                    Toast.LENGTH_SHORT).show();
        }
        //action is basketball button
        if(arg1.getAction().equals("Basketball")){
            Toast.makeText(arg0, "A2 Receiver: Basketball was the chosen sport",
                    Toast.LENGTH_SHORT).show();
        }
    }
}