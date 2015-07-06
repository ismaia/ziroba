package net.bomtec.ziroba;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.Image;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends Activity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String host = prefs.getString(SettingsActivity.PREF_HOSTTEXT_KEY, "");
        String port = prefs.getString(SettingsActivity.PREF_PORTTEXT_KEY, "");
        NetClient.getInstance().setup(host, port);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Intent intent = new Intent(this, SettingsActivity.class);
            startActivity(intent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }



    public void sendCommandA(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_A_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandUp(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_UP_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandB(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_B_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandLeft(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_LEFT_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandX(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_X_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandRight(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_RIGHT_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }
    public void sendCommandC(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_C_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }
    public void sendCommandDown(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_DOWN_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }
    public void sendCommandD(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_COMMAND_D_KEY, "");
        NetClient.getInstance().sendMessage(cmd);
    }


}
