package bgu.spl.net.srv;

public class User {
    private int connectionId;
    private String userName;
    private String password;
    private int port;
    private ConnectionHandler connectionHandler;
    private boolean isConnected = false;

    public User(String userName, String password, ConnectionHandler connectionHandler, boolean isConnected) {
        // this.connectionId = connectionId;
        this.userName = userName;
        this.password = password;
        this.connectionHandler = connectionHandler;
        this.isConnected = isConnected;
    }



    public String getUserName() {
        return userName;
    }

    public String getPassword() {
        return password;
    }

    public boolean isConnected() {
        return isConnected;
    }

    public void setConnected(boolean connected) {
        isConnected = connected;
    }

    public ConnectionHandler getConnectionHandler() {
        return connectionHandler;
    }

    public void setConnectionHandler(ConnectionHandler connectionHandler) {
        this.connectionHandler = connectionHandler;
    }
}


