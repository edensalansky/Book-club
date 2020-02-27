package bgu.spl.net.srv.Messages;

import bgu.spl.net.srv.ConnectionHandler;

public class message {
    private String destination;
    private String subId;
    private String msgId;
    private String msgBody;
    private String msg;
    private messageId messageId = bgu.spl.net.srv.Messages.messageId.getInstance();

    public message(String destination, String subId, String msgBody, String messageid) {
        this.destination = destination;
        this.subId = subId;
        this.msgId = messageid;
        this.msgBody = msgBody;
        this.msg=createMessage();
    }

    private String createMessage() {
        String str = "";
        str = "MESSAGE" + "\n"
                + "subscription:" + subId + "\n" +
                "Message-id:" + msgId + "\n" +
                "destination:" + destination + "\n\n" +
                msgBody ;
        return str;

    }

    public String getMsg() {
        return msg;
    }
}
