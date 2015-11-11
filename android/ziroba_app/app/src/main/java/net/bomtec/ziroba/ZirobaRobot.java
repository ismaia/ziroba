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
import java.net.SocketException;

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



    public synchronized void sendMessage(String msg) {

        if (socket != null) {
            buff = msg.getBytes();
            Thread thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        packet = new DatagramPacket(buff, buff.length, hostAddr, port);
                        socket.send(packet);
                        active = true;
                    } catch (Exception e) {
                        //stop();
                        e.printStackTrace();
                    }
                }
            });
            thread.start();
            try {
                thread.join(250);
            }catch (InterruptedException e) {

            }
        }else { //connect
            connect(host, port);
        }

    }



    public synchronized void stop() {
        try {
            if (socket != null) {
                socket.disconnect();
                socket.close();
                socket = null;
            }
        }catch (Exception e) {
            e.printStackTrace();
            socket = null;
        }
        active = false;
    }


    public  synchronized boolean connect(final String host, final int port) {
        this.host = host;
        this.port = port;
        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    hostAddr = InetAddress.getByName(host);
                    socket = new DatagramSocket(port);
                    socket.connect(hostAddr,port);
                    active = true;
                } catch (Exception e) {
                    stop();
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

        return active;
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
