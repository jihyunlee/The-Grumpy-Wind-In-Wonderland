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
        
	started = false;
	fullscreen = false;
	ofSetVerticalSync(true);
    if(bLocal)
        looping = true;
		
	// Set up OSC
	receiver.setup( port );
	
	// Load movie
	movie.loadMovie(movieFile);
	movie.play();
	movie.idleMovie();
		
	ofBackground( 0, 0, 0 );    
    ofEnableAlphaBlending();
    ofHideCursor();
    
    nRows = 20;
    if(bLocal)
        startY = 0;
    else
        startY = 0;
    endY = startY;
}


void wonderApp::update(){
	if (started) {
		movie.idleMovie();
	}
		
	// Check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// Get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		// Check for movie position info
		if ( m.getAddress() == "/movie/position" )
		{
			float p = m.getArgAsFloat(0);
			if (!started) {
				started = true;
				movie.play();
                // Turns looping off
                if (!looping) {
                    movie.setLoopState(OF_LOOP_NONE);
                } else {
                    movie.setLoopState(OF_LOOP_NORMAL);
                }
			}
			// Set the position
			movie.setPosition(p);
			
		}        
        else if(m.getAddress() == "/hangup") {
            string id = m.getArgAsString(0);
            
            for(int i=0; i<callers.size(); i++) {
                Caller* c = callers.at(i);
                if(c->isCaller(id)) {
                    callers.erase(callers.begin() + i);
                    endY -= ofGetWindowHeight()/nRows;
                }
            }
            if(bDebug) std::cout << "[LEFT] HANGUP:: number of callers" << callers.size() << "\n";
        }
        else if(m.getAddress() == "/newcaller") {
            
            string id = m.getArgAsString(0);
            string phoneNumber = m.getArgAsString(1);
            
            Caller* c = new Caller(id, phoneNumber);
            callers.push_back(c);  
            endY += ofGetWindowHeight()/nRows;
            
            if(bDebug) std::cout << "[LEFT] CALLER(" << callers.size() << "):: " << phoneNumber << "\n";
        }
    }
}


void wonderApp::draw(){
    
	movie.draw(movieX,movieY,movieWidth,movieHeight);
    
    // scrolling callers
    int lineHeight = ofGetWindowHeight()/nRows;
    int colX = 160;
    if(bLocal)
        colX = 10;

    if(callers.size() <= nRows) {
        
        for(int i=0; i<callers.size(); i++) {
            Caller* c = callers.at(i);
            c->draw(colX, startY-i*lineHeight);
        }
        
        if(startY != endY) {
            if(startY < endY)
                startY++;
            else
                startY--;
        }
    }
    else {
        
        int len = lineHeight*callers.size();
        
        for(int i=0; i<callers.size(); i++) {
            int h = i*lineHeight;
            Caller* c = callers.at(i);
            c->draw(colX, startY - h);
            c->draw(colX, startY - h + len);
            c->draw(colX, startY - h - len);
        }        
        
        if(startY != endY) {
            if(startY < endY)
                startY+=0.5;
        }
        else {
            startY = 0;
        }
    }
}


void wonderApp::loadSettings(string fileString){
	
	
	//--------------------------------------------- get configs
    ofxXmlSettings xmlReader;
	
	bool result = xmlReader.loadFile(fileString);
	
	if(!result) printf("error loading xml file\n");
	
	int w = xmlReader.getValue("settings:dimensions:width", 640, 0);
	int h = xmlReader.getValue("settings:dimensions:height", 480, 0);
	
	movieWidth = xmlReader.getValue("settings:dimensions:movieWidth", 640, 0);
	movieHeight = xmlReader.getValue("settings:dimensions:movieHeight", 480, 0);
	
	movieX = xmlReader.getValue("settings:dimensions:movieX", 640, 0);
	movieY = xmlReader.getValue("settings:dimensions:movieY", 480, 0);
	
	port = xmlReader.getValue("settings:port",9999,0);
	
	string filename = xmlReader.getValue("settings:movie:","test",0);
	movieFile = (char *) malloc(sizeof(char)*filename.length());
	strcpy(movieFile, filename.c_str());
	
	ofSetWindowShape(w, h);
	
	if(xmlReader.getValue("settings:go_fullscreen", "false", 0).compare("true") == 0) {
		fullscreen = true;
		ofSetFullscreen(true);
	}
    
    if(xmlReader.getValue("settings:loop", "false", 0).compare("true") == 0) {
		looping = true;
	}
}

// for test
void wonderApp::keyPressed(int key){
    double n = 7083 + int(ofRandom(-999,999));
    string s = "646606" + ofToString(n);
    
    if (key == OF_KEY_UP){
        Caller* c = new Caller(ofToString(callers.size()), s);
        callers.push_back(c);
        endY += ofGetWindowHeight()/nRows;
        
        
    } else if (key == OF_KEY_DOWN){
        if(callers.size() > 0) {
            int i = ofRandom(0,callers.size());
            Caller* c = callers.at(i);
            callers.erase(callers.begin() + i);
            endY -= ofGetWindowHeight()/nRows;
        }
    }
    
    if(bDebug) std::cout << "[LEFT] mousePressed:: " << callers.size() << "\n";        
}