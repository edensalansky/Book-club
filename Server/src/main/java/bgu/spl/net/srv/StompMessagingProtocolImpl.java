package bgu.spl.net.srv;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Command.*;
import bgu.spl.net.srv.Messages.messageId;

public class StompMessagingProtocolImpl<T> implements StompMessagingProtocol<T> {
    private boolean shouldTerminate = false;
    private int connectionId;
    private ConnectionHandler connectionHandler;
    private messageId messageID=messageId.getInstance();

    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connectionId = connectionId;
        ConnectionsImpl temp = (ConnectionsImpl) connections;
        this.connectionHandler = temp.getHandler(connectionId);
    }

    @Override
    public void process(String message) {
       // System.out.println(message+"\n");
        String command = message.substring(0, message.indexOf("\n"));
        if (command .equals("CONNECT"))
            new LoginCommand(message, connectionHandler,messageID.getId());
        else if (command .equals( "SUBSCRIBE"))
            new JoinGenre(message, connectionHandler);
        else if( command.equals(("UNSUBSCRIBE")))
            new exitGenre(message,connectionHandler);
        else if (command .equals("SEND"))
            new SendFrame(message, connectionHandler,messageID.getId());
        else if (command .equals("DISCONNECT"))
            new Logout(message, connectionHandler);
    }

    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
    public void setTerminate(boolean terminate){
        shouldTerminate = terminate;
    }
}
