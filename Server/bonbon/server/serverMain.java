package bonbon.server;

import org.apache.mina.core.service.IoAcceptor;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.charset.Charset;

/**
 * Created by mengjiangtao on 7/14/15.
 */
public class serverMain {

    private static final int PORT  = 9124;
    public static void main(String[] args) throws IOException{
        IoAcceptor acceptor = new NioSocketAcceptor();
        acceptor.getFilterChain().addLast("logger",new LoggingFilter());
        acceptor.getFilterChain().addLast("codec",new ProtocolCodecFilter(new TextLineCodecFactory(Charset.defaultCharset().forName("UTF-8"))));
        acceptor.setHandler(new serverHandle());
        acceptor.setDefaultLocalAddress(new InetSocketAddress(PORT));
        acceptor.bind();
    }
}
