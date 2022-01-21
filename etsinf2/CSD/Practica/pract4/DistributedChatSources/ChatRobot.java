// This file must be implemented when completing activity 2
//

import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;
import java.util.*;

//
// ChatRobot implementation
//
public class ChatRobot extends ChatClientCSD
{
    private String channel;
    
    public ChatRobot(ChatConfiguration conf) {
        super(conf);
        try{
            this.doConnect(conf.getServerName(),"bot");
            this.doJoinChannel(conf.getChannelName());
            channel = conf.getChannelName();
        }
        catch(Exception e){System.out.println(e.toString());}
    }

    @Override
    public void messageArrived(IChatMessage msg) {
        try {
            IChatUser src = msg.getSender();
            Remote dst = msg.getDestination();
            String str = msg.getText();

            if (str.startsWith (ChatChannel.JOIN)) {
                String nick = str.substring (ChatChannel.JOIN.length() + 1);
                this.doSendChannelMessage (channel, "Hola "+nick);
            }
        } catch (Exception e) {}
    }

    public static void main (String args [] )
    {
        try{
            ChatRobot cc = new ChatRobot(ChatConfiguration.parse(args));
        }
        catch(Exception e){}
    }
}
