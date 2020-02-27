package bgu.spl.net.srv.Command;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.Messages.receipt;

import java.io.IOException;

public class Logout {
    private ConnectionsImpl connections = ConnectionsImpl.getInstance();
    private String msg;
    private ConnectionHandler connectionHandler;
    private String receiptID;

    public Logout(String msg, ConnectionHandler connectionHandler)  {
        this.connectionHandler= connectionHandler;
        this.msg=msg;
        msg = msg.substring(msg.indexOf("\n")+1);
        this.receiptID = msg.substring(msg.indexOf(":")+1);
        String toSend = process();
        try {
            connectionHandler.send(toSend);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public String process(){
        connections.disconnect(connections.getMapofConnID().get(connectionHandler));
        return new receipt(receiptID).getMsg();
    }
}
