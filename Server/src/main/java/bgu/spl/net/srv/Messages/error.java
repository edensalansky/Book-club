package bgu.spl.net.srv.Messages;

public class error {
    private String receiptId;
    private String message;
    private String msgBody;
    private String reason;
    private String answer;


    public error(String receiptId, String message, String reason) {
        this.receiptId = receiptId;
        this.message = message;
        this.reason = reason;
        answer=createError();

    }

    public String createError() {
        String str = "";
        str = "ERROR" + "\n"
                + "receipt-id: " + receiptId + "\n"
                + "message: " + message + "\n\n"
                + reason ;
        return str;

    }

    public String getAnswer() {
        return answer;
    }
}
