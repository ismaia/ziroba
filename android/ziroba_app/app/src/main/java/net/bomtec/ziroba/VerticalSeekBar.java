package net.bomtec.ziroba;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.widget.SeekBar;
import android.view.MotionEvent;

import java.util.Arrays;


public class VerticalSeekBar extends SeekBar{

    private static int progressTable[];
    private static boolean flag = true;
    private String resName = "";

    private OnSeekBarChangeListener mOnSeekBarChangeListener;


    public VerticalSeekBar(Context context) {
        super(context);
    }

    public VerticalSeekBar(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);

    }

    public VerticalSeekBar(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(h, w, oldh, oldw);
    }

    @Override
    protected synchronized void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(heightMeasureSpec, widthMeasureSpec);
        setMeasuredDimension(getMeasuredHeight(), getMeasuredWidth());
    }

    protected void onDraw(Canvas c) {
        c.rotate(-90);
        c.translate(-getHeight(), 0);

        super.onDraw(c);
    }



    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (!isEnabled()) {
            return false;
        }

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_MOVE:
                int progress = getMax() - (int) (getMax() * event.getY() / getHeight());
                setProgress(progress);
                onSizeChanged(getWidth(), getHeight(), 0, 0);
                break;
            case MotionEvent.ACTION_CANCEL:
                break;
        }
        return true;
    }

    static int oldZProgress = 0;

    public void initChangeListener() {


        mOnSeekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                int newZProgress = progressTable[progress];

                String action = "";
                String value  = "";
                String msg    = "";

               if (oldZProgress == 0) {
                   if (newZProgress > 0) {
                       action = "setdir";
                       value = "1";
                   } else if (newZProgress < 0) {
                       action = "setdir";
                       value = "0";
                   }
               }

                if (action != "") {
                    msg = resName + ":" +  action + ":" + value;
                    CmdClient.getInstance().sendMessage(msg);
                }


                if (newZProgress != oldZProgress) {
                    action = "setduty";
                    msg = resName + ":" + action + ":" + Integer.toString(Math.abs(newZProgress));
                    CmdClient.getInstance().sendMessage(msg);
                }


                oldZProgress = newZProgress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        };
        setOnSeekBarChangeListener(mOnSeekBarChangeListener);
    }


    public synchronized void init() {
        setProgress(getMax()/2);
        resName = getResources().getResourceEntryName(getId());
        CmdClient.getInstance().sendMessage(resName + ":setduty:" + "0");

        if (flag) {
            progressTable = new int[getMax()+10];
            Arrays.fill(progressTable, 0 , 10 , 100);
            Arrays.fill(progressTable, 10, 20 , 75);
            Arrays.fill(progressTable, 20, 30 , 50);
            Arrays.fill(progressTable, 30, 40 , 25);
            Arrays.fill(progressTable, 40, 44 , 10);
            Arrays.fill(progressTable, 45, 55 , 0);
            Arrays.fill(progressTable, 56, 60 , -10);
            Arrays.fill(progressTable, 60, 70 , -25);
            Arrays.fill(progressTable, 70, 80 , -50);
            Arrays.fill(progressTable, 80, 90 , -75);
            Arrays.fill(progressTable, 90, 101, -100);
            flag = false;
        }

        this.initChangeListener();

    }

    public void progress50() {
        setProgress(getMax() / 2);
        CmdClient.getInstance().sendMessage(getResources().getResourceEntryName(getId()) + ":0" + "0");
    }


}