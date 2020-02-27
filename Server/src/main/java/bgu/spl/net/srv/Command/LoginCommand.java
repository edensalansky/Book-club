package bgu.spl.net.srv.Command;

import bgu.spl.net.srv.BlockingConnectionHandler;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.Messages.connected;
import bgu.spl.net.srv.Messages.error;
import bgu.spl.net.srv.User;
import com.sun.org.apache.xerces.internal.impl.xs.XSComplexTypeDecl;

import javax.swing.*;
import java.io.IOException;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class LoginCommand {
    private ConnectionsImpl connections = ConnectionsImpl.getInstance();
    private String name;
    private String password;
    private String msg;
    private ConnectionHandler connectionHandler;
    private String messageId;

    public LoginCommand(String message, ConnectionHandler connectionHandler, int messageID) {
        this.messageId=String.valueOf(messageID);
        this.connectionHandler = connectionHandler;
        this.msg = message;
        msg = msg.substring(msg.indexOf("\n")+1);
        msg = msg.substring(msg.indexOf("\n")+1);
        msg = msg.substring(msg.indexOf("\n")+1);
        name = msg.substring(msg.indexOf(":")+1, msg.indexOf("\n"));
        msg = msg.substring(msg.indexOf("\n")+1);
        password = msg.substring(msg.indexOf(":")+1);
        String toSend = process();
        try {
            connectionHandler.send(toSend);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String process() {
        Set<Map.Entry<Integer, User>> entrySet = connections.getMapOfUser().entrySet();
        Iterator<Map.Entry<Integer, User>> itr = entrySet.iterator();
        while (itr.hasNext()) {
            Map.Entry<Integer, User> entry = itr.next();
            User value = entry.getValue();
            if (value.getUserName().equals(name) ) {
                if (!value.isConnected()) {
                    if (!value.getPassword().equals(password))
                        return new error(messageId, "Wrong password", "Wrong password").getAnswer();

                    else {
                        value.setConnected(true);
                        value.setConnectionHandler(connectionHandler);
                        return new connected().getMsg();
                    }
                } else
                    return new error(messageId, "User already logged in", "User already logged in").getAnswer();
            }
        }
        add(name, new User(name, password, connectionHandler, true));
        return new connected().getMsg();

    }
    private void add(String name, User user) {
        connections.addToUserMap(name, user);
    }
}
