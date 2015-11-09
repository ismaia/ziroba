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
    private String resName      = "";
    private int mZDevice        = -1;  //This seekbar is assigned to a ziroba's device

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

                int    action = -1;
                int    value  = -1;
                String msg    = "";

                if (oldZProgress == 0) {
                    if (newZProgress > 0) {
                        value = 1;
                    } else if (newZProgress < 0) {
                        value = 0;
                    }
                }

                if (value != -1)
                    ZirobaRobot.getInstance().sendSetDirCmd(mZDevice, value);


                if (newZProgress != oldZProgress) {
                    action = ZirobaRobot.ZAction.SET_DUTY;
                    value  = Math.abs(newZProgress);
                    ZirobaRobot.getInstance().sendDutyCmd(mZDevice, value);
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

        //skb1 controls ziroba's dcmotor1
        if (getId() == R.id.skb1)
            mZDevice =  ZirobaRobot.ZDevice.DCMOTOR1;
        else if (getId() == R.id.skb2)
            mZDevice = ZirobaRobot.ZDevice.DCMOTOR2;


        if (flag) {
            progressTable = new int[getMax()+10];
            Arrays.fill(progressTable, 0 , 10 , 100);
            Arrays.fill(progressTable, 10, 20 , 90);
            Arrays.fill(progressTable, 20, 30 , 80);
            Arrays.fill(progressTable, 30, 40 , 70);
            Arrays.fill(progressTable, 40, 44 , 60);
            Arrays.fill(progressTable, 45, 55 , 0);
            Arrays.fill(progressTable, 56, 60 , -60);
            Arrays.fill(progressTable, 60, 70 , -70);
            Arrays.fill(progressTable, 70, 80 , -80);
            Arrays.fill(progressTable, 80, 90 , -90);
            Arrays.fill(progressTable, 90, 101, -100);
            flag = false;
        }

        this.initChangeListener();

    }


}