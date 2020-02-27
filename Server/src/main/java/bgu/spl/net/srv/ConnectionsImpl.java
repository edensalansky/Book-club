package bgu.spl.net.srv;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl implements Connections<String> {
    private ConcurrentHashMap<ConnectionHandler, Integer> mapofConnID = new ConcurrentHashMap<>();
    private ConcurrentHashMap<Integer, ConnectionHandler> mapofHandlers = new ConcurrentHashMap<>();
    private ConcurrentHashMap<String, List<Pair<ConnectionHandler, String>>> mapOfChan = new ConcurrentHashMap<>();
    private ConcurrentHashMap<String , User> mapOfUsers=new ConcurrentHashMap();


    private static class SingletonHolder {
        private static ConnectionsImpl instance = new ConnectionsImpl();
    }
    public static ConnectionsImpl getInstance() {
        return SingletonHolder.instance;
    }

    public boolean send(int connectionId, String msg) {
        ConnectionHandler connectionHandler = mapofHandlers.get(connectionId);
        if (connectionHandler != null) {
            try {
                connectionHandler.send(msg);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return true;
        }
        return false;
    }


    public void send(String channel, String msg) {
        for (Pair<ConnectionHandler,String> pair : mapOfChan.get(channel)) {
            try {
                pair.getFirst().send(msg);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


    public void disconnect(int connectionId) {
        if (mapofHandlers.get(connectionId) != null) {
            ConnectionHandler handler = mapofHandlers.get(connectionId);
            mapofHandlers.remove(connectionId);
            mapofConnID.remove(handler);
            Set<Map.Entry<String, List<Pair<ConnectionHandler, String>>>> entrySet = mapOfChan.entrySet();
            Iterator<Map.Entry<String, List<Pair<ConnectionHandler, String>>>> itr = entrySet.iterator();
            while (itr.hasNext()) {
                Map.Entry<String, List<Pair<ConnectionHandler, String>>> entry = itr.next();
                String key = entry.getKey();
                List<Pair<ConnectionHandler, String>> value = entry.getValue();
                for (Pair<ConnectionHandler, String> pair : value) {
                    if (pair.getFirst() == handler) {
                        mapOfChan.get(key).remove(pair);
                    }
                }
            }


            Set<Map.Entry<String, User>> entrySet2= getMapOfUser().entrySet();
            Iterator<Map.Entry<String, User>> itr2 = entrySet2.iterator();
            while (itr2.hasNext()) {
                Map.Entry<String, User> entry = itr2.next();
                User value = entry.getValue();
                if (value.getConnectionHandler() == handler)
                    value.setConnected(false);
            }
        }
    }

    public void addClient(ConnectionHandler handler, int id) {
        mapofHandlers.put(id, handler);
        mapofConnID.put(handler,id);

        id++;
    }

    public void addToChan(String chan, ConnectionHandler handler, String subID) {
        if (mapOfChan.get(chan) != null)
            mapOfChan.get(chan).add(new Pair(handler,subID));
        else {
            mapOfChan.put(chan, new LinkedList<>());
            mapOfChan.get(chan).add(new Pair(handler,subID));
        }
    }

    public void removeFromChan(String chan,ConnectionHandler handler){
        mapOfChan.get(chan).remove(handler);
    }

    public ConcurrentHashMap<String, List<Pair<ConnectionHandler, String>>> getMapOfChan() {
        return mapOfChan;
    }
    public List<Pair<ConnectionHandler, String>> getChannelID(String channel) {
        if (mapOfChan.containsKey(channel))
            return mapOfChan.get(channel);
        return null;

    }
    public ConnectionHandler getHandler(int id){
        return mapofHandlers.get(id);
    }
    public ConcurrentHashMap getMapOfUser(){
        return mapOfUsers;
    }
    public void addToUserMap(String  name, User user){
        mapOfUsers.put(name,user);
    }
    public ConcurrentHashMap<Integer, ConnectionHandler> getMapofHandlers() {
        return mapofHandlers;
    }
    public ConcurrentHashMap<ConnectionHandler, Integer> getMapofConnID() {
        return mapofConnID;
    }

}
