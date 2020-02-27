package bgu.spl.net.srv;

public class Pair<T,F>{
    private T first;
    private F second;

    public Pair(T first, F second){
        this.first = first;
        this.second = second;
    }
    public void setFirst(T first){
        this.first=first;
    }
    public void setSecond(F second){
        this.second=second;
    }
    public T getFirst(){
        return first;
    }
    public F getSecond(){
        return second;
    }
}
