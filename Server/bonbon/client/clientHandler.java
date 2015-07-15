package bonbon.client;

import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;

/**
 * Created by mengjiangtao on 7/14/15.
 */
public class clientHandler extends IoHandlerAdapter {

    @Override
    public void messageReceived(IoSession session,Object message) throws  Exception {
        System.out.println(message);
    }
}
