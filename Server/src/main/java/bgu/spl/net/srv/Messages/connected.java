package bgu.spl.net.srv.Messages;

public class connected {
    String msg;
    public connected() {
        msg=createConnected();
    }

    public String getMsg() {
        return msg;
    }

    public String createConnected() {
        String str = "";
        str = "CONNECTED" + "\n" + "version:1.2" + "\n\nLogin successful";
        return str;
    }
}
