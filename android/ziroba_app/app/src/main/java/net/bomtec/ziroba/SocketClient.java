package net.bomtec.ziroba;


import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class SocketClient  {

    private Socket mSocket;
    private PrintWriter out;
    private BufferedReader in;

    public SocketClient(String host, int port) {
        try {
            InetAddress addr = InetAddress.getByName(host);
            mSocket = new Socket(addr, port);
            out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(mSocket.getOutputStream())), true);
        }catch ( UnknownHostException e1) {
            Log.e("SocketClient", "C: Sent.",e1);
        }catch (IOException e2) {
            Log.e("SocketClient", "S: Error", e2);
        }

    }


    public void sendMessage(String msg) {
        if (out != null && !out.checkError()) {
            out.print(msg);
            out.flush();
        }
    }


}
