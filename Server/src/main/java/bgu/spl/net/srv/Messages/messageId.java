package bgu.spl.net.srv.Messages;

import bgu.spl.net.srv.ConnectionsImpl;

import java.util.concurrent.atomic.AtomicInteger;

public class messageId {
    private AtomicInteger id=new AtomicInteger();
    private static class SingletonHolder {
        private static messageId instance = new messageId();
    }
    public static messageId getInstance() {
        return messageId.SingletonHolder.instance;
    }

    public int getId() {
        return id.getAndIncrement();
    }
}
