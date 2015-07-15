package bonbon.client;

import org.apache.mina.core.future.ConnectFuture;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketConnector;

import java.net.InetSocketAddress;
import java.nio.charset.Charset;

/**
 * Created by mengjiangtao on 7/14/15.
 */
public class main {
    public static void main(String[] args){
        NioSocketConnector connector = new NioSocketConnector();
        connector.getFilterChain().addLast("logger",new LoggingFilter());
        connector.getFilterChain().addLast("codec", new ProtocolCodecFilter(new TextLineCodecFactory(Charset.forName("UTF-8"))));
        connector.setHandler(new clientHandler());
        ConnectFuture cf = connector.connect(new InetSocketAddress("127.0.0.1",9124));
        cf.awaitUninterruptibly();
        cf.getSession().write("getTime");
        cf.getSession().write("quit");
        cf.getSession().getCloseFuture().awaitUninterruptibly();
        connector.dispose();
    }
}
