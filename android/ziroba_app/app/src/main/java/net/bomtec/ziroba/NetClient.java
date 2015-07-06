package net.bomtec.ziroba;


import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;


/**
 * Socket Client
 * Used to send commands to the remote destination
 * @author Isaac Maia
 */

public class NetClient   {
    private String host;
    private int port;
    private InetAddress hostAddr;
    private Socket socket = null;
    private volatile boolean active = false;
    private Thread thread;

    private static volatile NetClient instance = null;

    /**
     * setHost and setPort must be callled
     * @return a unique instance of NetClient
     */
    public static synchronized NetClient getInstance() {
        if (instance == null) {
            instance = new NetClient();
        }
        return instance;
    }

    private NetClient() {}


    public synchronized void start() {
        if (!active) {
            thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        hostAddr = InetAddress.getByName(host);
                        socket = new Socket(hostAddr, port);
                        active = true;
                    } catch (Exception e) {
                        active = false;
                        socket = null;
                        e.printStackTrace();
                    }
                }
            });
            thread.start();
        }
    }


    public void join() {
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void setup(String host, String port) {
        this.host = host;
        this.port = Integer.parseInt(port);
    }


    public synchronized void sendMessage(String msg) {
        final String message = msg;
        if (socket != null) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())),
                                true);
                        out.print(message);
                        out.flush();
                        active = true;
                    } catch (Exception e) {
                        e.printStackTrace();
                        active = false;
                    }
                }
            }).start();
        }
    }

    public synchronized void stop() {
        socket = null;
        active = false;
    }

    public synchronized boolean isActive() {
        return (active);
    }


}
