package net.bomtec.ziroba;


import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;


/**
 * TCP Socket Client
 * Handles command messages to the server (the robot)
 * @author Isaac Maia
 */

public class CmdClient {
    private String host;
    private int port;
    private InetAddress hostAddr;
    private Socket socket = null;
    private volatile boolean active = false;
    private Thread thread;

    private static volatile CmdClient instance = null;

    /**
     * setHost and setPort must be callled
     * @return a unique instance of CmdClient
     */
    public static synchronized CmdClient getInstance() {
        if (instance == null) {
            instance = new CmdClient();
        }
        return instance;
    }

    private CmdClient() {}


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
            thread.join(2000);
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
