package bgu.spl.net.srv.Command;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.Messages.message;
import bgu.spl.net.srv.Pair;

import java.io.IOException;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class SendFrame {
        private String destination;
        private String msg;
        private String subId;
        private String msgBody;
        private ConnectionHandler connectionHandler;
        private ConnectionsImpl connections=ConnectionsImpl.getInstance();
        private String messageId;


        public SendFrame(String message, ConnectionHandler connectionHandler, int messageID) {
            this.messageId = String.valueOf(messageID);
            this.connectionHandler = connectionHandler;
            this.msg = message;
            message = message.substring(message.indexOf("\n") + 1);
            destination = message.substring(message.indexOf(":") + 1, message.indexOf("\n"));
            message = message.substring(message.indexOf("\n") + 1);
            message = message.substring(message.indexOf("\n") + 1);
            if(message.contains("\n"))
                message = message.substring(message.indexOf("\n") + 1);
            msgBody = message;
            List<Pair<ConnectionHandler, String>> IDs = connections.getChannelID(destination);
            if (IDs != null) {
                for (int i = 0; i < IDs.size(); i++) {
                    try {
                        subId = IDs.get(i).getSecond();
                        String toSend = process();
                        IDs.get(i).getFirst().send(toSend);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        public String process(){
            return new message(destination,  subId,  msgBody, messageId).getMsg();
        }

    }
