package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicInteger;


public class BlockingConnectionHandler<T> implements Runnable, ConnectionHandler<T> {

    private final StompMessagingProtocolImpl protocol;
    private final MessageEncoderDecoderImp encdec;
    private final Socket sock;
    private BufferedInputStream in;
    private BufferedOutputStream out;
    private volatile boolean connected = true;
    private int connectionID;
    private Connections connections;



    public BlockingConnectionHandler(Socket sock, MessageEncoderDecoderImp reader, StompMessagingProtocolImpl protocol, int connectionID,Connections connections1) {
        this.sock = sock;
        this.encdec = reader;
        this.protocol = protocol;
        this.connectionID = connectionID;
        this.connections=connections1;
    }

    @Override
    public void run() {
        try (Socket sock = this.sock) { //just for automatic closing
            int read;;
            in = new BufferedInputStream(sock.getInputStream());
            out = new BufferedOutputStream(sock.getOutputStream());
            while (!protocol.shouldTerminate() && connected && (read = in.read()) >= 0) {
                String nextMessage = (String) encdec.decodeNextByte((byte) read);
                if (nextMessage != null) {
                    protocol.process(nextMessage);

                }
            }
            protocol.setTerminate(true);

        } catch (IOException ex) {
            ex.printStackTrace();
        }

    }

    @Override
    public void close() throws IOException {
        connected = false;
        sock.close();
    }

    @Override
    public synchronized void  send(T msg) {
        try {
            if (msg != null) {
                out.write(encdec.encode((java.lang.String) msg));
                out.flush();
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public StompMessagingProtocol getProtocol() {
        return protocol;
    }


}
