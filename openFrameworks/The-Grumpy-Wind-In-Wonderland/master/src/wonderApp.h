#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "caller.h"

#define HOST "localhost"
#define PORT 12345

#define NUM_MSG_STRINGS 30


class wonderApp : public ofBaseApp {

public:

    void setup();
    void loadSettings(string fileString);
    
    void update();
    void draw();
    
    
	ofVideoPlayer 		movie;

	
	int count;
	int howOften;
	
	bool started;
	bool fullscreen;
	
	char * movieFile;
	char * host1;
	char * host2;
	int port1;
	int port2;
	
	int movieWidth;
	int movieHeight;
	int movieX;
	int movieY;
	
	bool looping;
	
	bool frameByframe;
	
	
	ofxOscSender sender1;
	ofxOscSender sender2;
    
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    bool bLocal;
    bool bDebug;
    

};

