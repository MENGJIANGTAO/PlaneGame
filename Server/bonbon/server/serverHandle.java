package bonbon.server;

import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;

import java.util.Date;

/**
 * Created by mengjiangtao on 7/14/15.
 */
public class serverHandle extends IoHandlerAdapter{


    @Override
    public void sessionCreated(IoSession session){
        System.out.print(session.getRemoteAddress().toString() + "has connection server.");
    }

    @Override
    public void messageReceived(IoSession session,Object message) throws Exception{
        String str = message.toString();
        if(str.trim().equalsIgnoreCase("quit")){
            session.close(true);
            return;
        }
        if(str.trim().equalsIgnoreCase("getTime")) {
            Date date = new Date();
            session.write(date.toString());
        }
    }

}
