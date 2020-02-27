
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.newsfeed.NewsFeed;
import bgu.spl.net.srv.BaseServer;
import bgu.spl.net.srv.MessageEncoderDecoderImp;
import bgu.spl.net.srv.Server;
import bgu.spl.net.srv.StompMessagingProtocolImpl;


public class main {

    public static void main(String[] args) {

    if(args.length < 2)
        System.out.println("not enough arguments");
    else{
        int port = Integer.parseInt(args[0]);
        if (args[1].equals("tpc")){
            Server.threadPerClient(port,()->new StompMessagingProtocolImpl<>(),
                    ()->new MessageEncoderDecoderImp<>()).serve();
        }
        else if (args[1].equals("reactor")){
            Server<String> reactor = Server.reactor(Runtime.getRuntime().availableProcessors(),port,()->new StompMessagingProtocolImpl<>(),()->new MessageEncoderDecoderImp<>());
            reactor.serve();
        }
    }


    }
}







