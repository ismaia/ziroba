package net.bomtec.ziroba;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.SeekBar;
import android.widget.Switch;

import java.util.Arrays;


public class MainActivity extends Activity {
    private SharedPreferences sharedPreferences;
    public static Activity mainActivt;
    Switch connSw;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mainActivt = this;
        setContentView(R.layout.activity_main);

        //read default preferences values
        PreferenceManager.setDefaultValues(this, R.xml.pref_general, true);
        PreferenceManager.setDefaultValues(this, R.xml.pref_buttons, true);
        sharedPreferences= PreferenceManager.getDefaultSharedPreferences(this);

        initViewsBehavior();

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


    private static int seekBarProgress = 0;
    private static int seekBarprogressTable[];
    private static boolean zflag = true;

    private synchronized void initViewsBehavior() {

        VerticalSeekBar seekBar1 = (VerticalSeekBar)findViewById(R.id.skb1);
        seekBar1.init();

        VerticalSeekBar seekBar2 = (VerticalSeekBar)findViewById(R.id.skb2);
        seekBar2.init();

        Switch cameraSw = (Switch)findViewById(R.id.camera_switch);
        cameraSw.setChecked(false);
        boolean swState = cameraSw.isChecked();

        cameraSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                Log.d("CameraSW", "checked");
            }

        });


        SeekBar seekBar3 = (SeekBar)findViewById(R.id.skb3);

        if (zflag) {
            seekBarprogressTable= new int[seekBar3.getMax()+10];
            Arrays.fill(seekBarprogressTable, 0, 15,   0);
            Arrays.fill(seekBarprogressTable, 15, 30 , 60);
            Arrays.fill(seekBarprogressTable, 30, 45 , 70);
            Arrays.fill(seekBarprogressTable, 45, 60 , 80);
            Arrays.fill(seekBarprogressTable, 60, 75 , 90);
            Arrays.fill(seekBarprogressTable, 75, 90 , 95);
            Arrays.fill(seekBarprogressTable, 90, 105 , 100);
            zflag = false;
        }

        seekBar3.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                seekBarProgress = seekBarprogressTable[progress];
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        connSw = (Switch)findViewById(R.id.connection_switch);

        connSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                String host = sharedPreferences.getString(SettingsActivity.PREF_KEY_HOST_TEXT, "");
                String port = sharedPreferences.getString(SettingsActivity.PREF_KEY_PORT_TEXT, "");
                if (isChecked) {
                    boolean status  = ZirobaRobot.getInstance().connect(mainActivt, host, port);
                    connSw.setChecked(status);
                }
            }

        });


        ImageButton butX = (ImageButton)findViewById(R.id.butX);

        butX.setOnTouchListener(
                new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN) {
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR1);
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR2);
                        }
                        return false;
                    }
                }
        );

        ImageButton butUp = (ImageButton)findViewById(R.id.butUp);
        butUp.setOnTouchListener(
                new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN) {
                            //Log.d("Button A", "clicked");
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR1, 0);
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR2, 0);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR1, seekBarProgress);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR2, seekBarProgress);

                        } else if (event.getAction() == MotionEvent.ACTION_UP) {
                            //Log.d("Button A", "released");
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR1);
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR2);
                        }
                        return false;
                    }
                }
        );

        ImageButton butLeft = (ImageButton)findViewById(R.id.butLeft);
        butLeft.setOnTouchListener(
                new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN) {
                            //Log.d("Button A", "clicked");
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR1, 0);
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR2, 1);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR1, seekBarProgress);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR2, seekBarProgress);
                        } else if (event.getAction() == MotionEvent.ACTION_UP) {
                            //Log.d("Button A", "released");
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR1);
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR2);
                        }
                        return false;
                    }
                }
        );

        ImageButton butRight = (ImageButton)findViewById(R.id.butRight);
        butRight.setOnTouchListener(
                new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN) {
                            //Log.d("Button A", "clicked");
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR1, 1);
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR2, 0);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR1, seekBarProgress);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR2, seekBarProgress);
                        } else if (event.getAction() == MotionEvent.ACTION_UP) {
                            //Log.d("Button A", "released");
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR1);
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR2);
                        }
                        return false;
                    }
                }
        );

        ImageButton butDown = (ImageButton)findViewById(R.id.butDown);
        butDown.setOnTouchListener(
                new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN) {
                            //Log.d("Button A", "clicked");
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR1, 1);
                            ZirobaRobot.getInstance().sendSetdirCmd(ZirobaRobot.ZDevice.DCMOTOR2, 1);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR1, seekBarProgress);
                            ZirobaRobot.getInstance().sendDutyCmd(ZirobaRobot.ZDevice.DCMOTOR2, seekBarProgress);
                        } else if (event.getAction() == MotionEvent.ACTION_UP) {
                            //Log.d("Button A", "released");
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR1);
                            ZirobaRobot.getInstance().sendStopCmd(ZirobaRobot.ZDevice.DCMOTOR2);
                        }
                        return false;
                    }
                }
        );




    }


}
