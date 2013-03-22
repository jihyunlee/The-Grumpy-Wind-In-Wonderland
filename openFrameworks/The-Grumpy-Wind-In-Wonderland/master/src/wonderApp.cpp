#include "wonderApp.h"


void wonderApp::setup(){

    bLocal = false;
    bDebug = false;

    // Load initial settings
    if(bLocal) {
        loadSettings("settings_local.xml");
    }
    else {
        loadSettings("settings.xml"); // NYU or IAC
    } 

	looping = false;
    if(bLocal)
        looping = true;

	started = false;
	fullscreen = false;
	count = 0;	
    
	ofSetVerticalSync(true);
	
	// open an outgoing connection to HOST:PORT
	sender1.setup( host1, port1 );
	sender2.setup( host2, port2 );

    receiver.setup(PORT);
    current_msg_string = 0;
    
    
	// Load movie file
	movie.loadMovie(movieFile);
	movie.play();
	
	// Turns looping off
	if (!looping) {
		movie.setLoopState(OF_LOOP_NONE);
	} else {
		movie.setLoopState(OF_LOOP_NORMAL);
	}
	
	ofBackground( 0, 0, 0 );
    ofHideCursor();    
}


void wonderApp::update(){
    
    /////////////////////////////////////////////
    // SENDING OSC
        
	movie.idleMovie();
	float p = movie.getPosition();
	
	// Broadcast current position information of movie
	if ((!started || count % howOften == 0)) {
		ofxOscMessage m;
		m.setAddress( "/movie/position" );
		m.addFloatArg(p);
		sender1.sendMessage(m);
		sender2.sendMessage(m);
		started = true;
	}
	count++;

        
    // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

        
    /////////////////////////////////////////////
    // RECEIVING OSC
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

        if(m.getAddress() == "/hangup") {
            string id = m.getArgAsString(0);                        
            if(bDebug) std::cout << "[MASTER] HANGUP:: " << id << "\n";
        }
        else if(m.getAddress() == "/newcaller") {
            string id = m.getArgAsString(0);            
            if(bDebug) std::cout << "[MASTER] CALLER::" << id << ")\n";
        }
	}
}


void wonderApp::draw(){
    
	movie.draw(movieX,movieY,movieWidth,movieHeight);    
}


void wonderApp::loadSettings(string fileString){
	
	string host_address1;
	string host_address2;
	string filename;
	
	//--------------------------------------------- get configs
    ofxXmlSettings xmlReader;
	bool result = xmlReader.loadFile(fileString);
	if(!result) printf("error loading xml file\n");
	
	host_address1 = xmlReader.getValue("settings:client1:address","test",0);
	port1 = xmlReader.getValue("settings:client1:port",5204,0);
	host1 = (char *) malloc(sizeof(char)*host_address1.length());
	strcpy(host1, host_address1.c_str());
	
	host_address2 = xmlReader.getValue("settings:client2:address","test",0);
	port2 = xmlReader.getValue("settings:client2:port",5204,0);
	host2 = (char *) malloc(sizeof(char)*host_address2.length());
	strcpy(host2, host_address2.c_str());
	
	filename = xmlReader.getValue("settings:movie:","test",0);
	movieFile = (char *) malloc(sizeof(char)*filename.length());
	strcpy(movieFile, filename.c_str());
	
	howOften = xmlReader.getValue("settings:howoften",60,0);
	
	int w = xmlReader.getValue("settings:dimensions:width", 640, 0);
	int h = xmlReader.getValue("settings:dimensions:height", 480, 0);
	
	movieWidth = xmlReader.getValue("settings:dimensions:movieWidth", 640, 0);
	movieHeight = xmlReader.getValue("settings:dimensions:movieHeight", 480, 0);
	
	movieX = xmlReader.getValue("settings:dimensions:movieX", 640, 0);
	movieY = xmlReader.getValue("settings:dimensions:movieY", 480, 0);
	
	ofSetWindowShape(w, h);
	
	if(xmlReader.getValue("settings:loop", "false", 0).compare("true") == 0) {
		looping = true;
	}
	
	if(xmlReader.getValue("settings:go_fullscreen", "false", 0).compare("true") == 0) {
		fullscreen = true;
		ofSetFullscreen(true);
	}
}