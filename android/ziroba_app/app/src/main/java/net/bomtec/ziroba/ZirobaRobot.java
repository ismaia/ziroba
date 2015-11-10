package net.bomtec.ziroba;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.util.Log;

import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;

/**
 * Created by isaac
 */
public class ZirobaRobot {

    private static ZirobaRobot instance = null;
    private DatagramSocket     socket = null;


    private String             host;
    private int                port;
    private InetAddress        hostAddr;
    private boolean            active = false;
    private DatagramPacket     packet;
    byte[]                     buff = null;
    private Thread             thread;

    public class ZDevice {
        public static final int DCMOTOR1 = 0;
        public static final int DCMOTOR2 = 1;
        public static final int CAMERA   = 2;
    }


    public class ZAction {
        public static final int SET_DUTY       = 0;
        public static final int SET_DIR        = 1;
        public static final int STOP           = 2;
        public static final int TOGGLE_DIR     = 3;
        public static final int ENABLE_CAMERA  = 4;
        public static final int DISABLE_CAMERA = 5;
    }


    private ZirobaRobot(){
        buff = new byte[128];
    }


    public void config(String host, String port) {
        this.host = host;
        this.port = Integer.parseInt(port);
    }


    public synchronized void sendMessage(String msg) {
        buff = msg.getBytes();

        if (socket != null) {
            Thread thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        packet = new DatagramPacket(buff, buff.length, hostAddr, port);
                        socket.send(packet);
                        active = true;
                    } catch (Exception e) {
                        socket.disconnect();
                        socket.close();
                        e.printStackTrace();
                        active = false;
                    }
                }
            });
            thread.start();
            try {
                thread.join(500);
            }catch (InterruptedException e) {

            }
        }

    }


    public String getHost() {
        return host;
    }

    public int getPort() {
        return port;
    }


    public boolean isActive() { return  active; }


    public synchronized void stop() {
        try {
            if (socket != null) {
                socket.disconnect();
                socket.close();
            }
        }catch (Exception e) {
            e.printStackTrace();
        }
        active = false;
    }


    public boolean connect(Context context, String host, String port) {
        this.host = host;
        this.port = Integer.parseInt(port);

        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    hostAddr = InetAddress.getByName(getHost());
                    socket = new DatagramSocket(getPort());
                    socket.connect(hostAddr,getPort());
                    active = true;
                } catch (Exception e) {
                    active = false;
                    socket.disconnect();
                    socket.close();
                    socket = null;
                    e.printStackTrace();
                }
            }
        });
        thread.start();

        //Blocks the current Thread until the receiver finishes its execution and dies.
        try {
            thread.join(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


//        if ( socket == null || !socket.isConnected() ) {
//            AlertDialog.Builder builder = new AlertDialog.Builder(context);
//            builder.setTitle("Connection");
//            builder.setMessage(R.string.dialog_connection_text);
//            builder.setCancelable(true);
//            builder.setNeutralButton("OK", new DialogInterface.OnClickListener() {
//                public void onClick(DialogInterface dialog, int id) {
//                    dialog.cancel();
//                }
//            });
//            builder.create();
//            builder.show();
//            return false;
//        }

        return true;
    }



    public static ZirobaRobot getInstance() {
        if (instance==null)
            instance = new ZirobaRobot();
        return instance;
    }



    public void mapZDeviceToResource(String resName, ZDevice dev) {
        //deviceMap.put(resName, Integer.valueOf(dev));
    }

    /**
     * Sends a formatted command to a specific ziroba's device
     * Format: dddd:aaaa:vvvvvvvv
     * @param device The ziroba's device destination of the message
     * @param action The action to perform on the device
     * @param value  The value of the action*
     */
    public synchronized void sendCmdMsg(int device, int action, int value) {
        String dev = String.format("%04d", device);
        String act = String.format("%04d", action);
        String val = String.format("%08d", value);
        String msg = dev + ":" +  act + ":" + val;
        sendMessage(msg);
    }

    public void sendDutyCmd(int dev, int duty) {
        sendCmdMsg(dev, ZAction.SET_DUTY, duty);
    }

    public void sendSetdirCmd(int dev, int dir) {
        sendCmdMsg(dev,ZAction.SET_DIR, dir);
    }

    public void sendStopCmd(int dev) {
        sendCmdMsg(dev,ZAction.STOP, 0);
    }


}
