package bgu.spl.net.srv.Command;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.Messages.receipt;

import java.io.IOException;

public class JoinGenre {
    private String genre;
    private String receiptId;
    private String msg;
    private String subscribeId;
    private ConnectionHandler connectionHandler;
    private ConnectionsImpl connections=ConnectionsImpl.getInstance();

    public JoinGenre(String msg, ConnectionHandler connectionHandler) {
        this.connectionHandler=connectionHandler;
        this.msg = msg;
        msg = msg.substring(msg.indexOf("\n")+1);
        genre = msg.substring(msg.indexOf(":")+1, msg.indexOf("\n"));
        msg = msg.substring(msg.indexOf("\n")+1);
        this.subscribeId = msg.substring(msg.indexOf(":")+1, msg.indexOf("\n"));
        msg = msg.substring(msg.indexOf("\n")+1);
        this.receiptId = msg.substring(msg.indexOf(":")+1);
        String toSend=process();
        try {
            connectionHandler.send(toSend);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    public String process(){
        connections.addToChan(genre,connectionHandler,subscribeId);
        return new receipt(receiptId).getMsg();

    }
}
