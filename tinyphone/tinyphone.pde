
// The Grumpy Wind in Wonderland
// Big Screens 2012, ITP NYU

// Jihyun Lee
// www.hellojihyun.com

// Download tinyphone library from the link below 
// https://github.com/itp-redial/tinyphone


import com.itpredial.tinyphone.client.*;
import oscP5.*;
import netP5.*;

TinyphoneClient tp;
String host = "50.56.215.198";
int port = 12002;
String phoneNumber = "1(206)279-5403";

OscP5 oscP5;
NetAddress master;
NetAddress clientL;
NetAddress clientR;

// Local
//String masterHost = "127.0.0.1";
//String clientLeftHost = "127.0.0.1";
//String clientRightHost = "127.0.0.1";
//int masterPort = 12345;
//int clientLeftPort = 12344;
//int clientRightPort = 12346;

// Remote
String masterHost = "192.168.130.241";
String clientLeftHost = "192.168.130.240";
String clientRightHost = "192.168.130.242";
int masterPort = 12345;
int clientLeftPort = 12345;
int clientRightPort = 12345;

ArrayList<Caller> callers = new ArrayList<Caller>();


void setup() {
  size(100,100);
  frameRate(4);
   
  tp = new TinyphoneClient(this, host, port, phoneNumber);
  tp.start();
  
  oscP5 = new OscP5(this, port);
  master = new NetAddress(masterHost, masterPort);
  clientL = new NetAddress(clientLeftHost, clientLeftPort);
  clientR = new NetAddress(clientRightHost, clientRightPort);
}

void draw() {}


//////////////////////////////////////////////////////////////////////////////////
//Tinyphone Events 

// called by tinyphone client when there's a new caller (required)
public void newCallerEvent(TinyphoneEvent event) {  

  // limited to 90 people due to limited numbers of channels assigned
  if(callers.size() > 90) 
    return;  
  
  String id = event.getId();
  String value = event.getCallerNumber();

  String msg = "n" + "," + id + "," + value;
//  println(msg);
  
  Caller c = new Caller(id, value);
  synchronized(callers) {
    callers.add(c);
    
    OscMessage myMessage = new OscMessage("/newcaller");
    myMessage.add(c.id);
    myMessage.add(c.phoneNumber);    
    oscP5.send(myMessage, master);
    oscP5.send(myMessage, clientL);
    oscP5.send(myMessage, clientR);
  } 
}

public void hangupEvent(TinyphoneEvent event) {

  String id = event.getId();
  
  String msg = "h" + "," + id;
//  println(msg);
  
  synchronized(callers) {
    for(int i=callers.size()-1; i>=0; i--) {
      Caller c = callers.get(i);

      if(c.isCaller(id)) {
        OscMessage myMessage = new OscMessage("/hangup");
        myMessage.add(c.id);
        oscP5.send(myMessage, master);
        oscP5.send(myMessage, clientL);
        oscP5.send(myMessage, clientR);
        
        callers.remove(callers.indexOf(c));
        break;       
      }
    }  
  }
}
