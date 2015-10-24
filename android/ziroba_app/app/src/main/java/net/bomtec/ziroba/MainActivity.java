package net.bomtec.ziroba;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.SeekBar;


public class MainActivity extends Activity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //read default preferences values
        PreferenceManager.setDefaultValues(this, R.xml.pref_general, true);
        PreferenceManager.setDefaultValues(this, R.xml.pref_buttons, true);

        SeekBar seekBar1 = (SeekBar)findViewById(R.id.seekbar1);


        seekBar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                CmdClient.getInstance().sendMessage("bar1:" + Integer.toString(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        SeekBar seekBar2 = (SeekBar)findViewById(R.id.seekbar2);


        seekBar2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                CmdClient.getInstance().sendMessage("Bar2:"+Integer.toString(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
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
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_A, "");
        CmdClient.getInstance().sendMessage(cmd);
        SeekBar seekBar1 = (SeekBar)findViewById(R.id.seekbar1);
        int progress = seekBar1.getMax()/2;
        seekBar1.setProgress(progress);

        SeekBar seekBar2 = (SeekBar)findViewById(R.id.seekbar2);
        progress = seekBar2.getMax()/2;
        seekBar2.setProgress( progress );
    }

    public void sendCommandB(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_B, "");
        CmdClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandC(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_C, "");
        CmdClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandD(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_D, "");
        CmdClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandE(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_E, "");
        CmdClient.getInstance().sendMessage(cmd);
    }


    public void sendCommandF(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_F, "");
        CmdClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandG(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_G, "");
        CmdClient.getInstance().sendMessage(cmd);
    }

    public void sendCommandH(View view) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String cmd = prefs.getString(SettingsActivity.PREF_KEY_COMMAND_H, "");
        CmdClient.getInstance().sendMessage(cmd);
    }



}
