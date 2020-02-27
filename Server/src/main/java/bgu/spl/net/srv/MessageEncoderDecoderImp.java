package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;

import javax.xml.bind.SchemaOutputResolver;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class MessageEncoderDecoderImp<T> implements MessageEncoderDecoder<T> {

    private byte[] bytes = new byte[1 << 10];
    private int len = 0;


    public T decodeNextByte(byte nextByte) {

        if (nextByte == '\u0000') {
            String str=popString();
            return (T)str;
        }
        pushByte(nextByte);
        return null;
    }





    @Override
    public byte[] encode(T message) {
        return (message + "\u0000").getBytes();
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }

        bytes[len++] = nextByte;
    }

    private String popString() {
        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);
        len = 0;
        return result;
    }
}


