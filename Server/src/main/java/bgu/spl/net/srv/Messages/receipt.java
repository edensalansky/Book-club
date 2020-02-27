package bgu.spl.net.srv.Messages;

public class receipt {
    private String receiptId;
    private String msg;

    public receipt(String receiptId) {
        this.receiptId = receiptId;
        msg = createReceipt();
    }

    public String createReceipt() {
        String str = "";
        str = "RECEIPT\n"
                + "receipt-id:" + receiptId;
        return str;
    }

    public String getMsg() {
        return msg;
    }
}
