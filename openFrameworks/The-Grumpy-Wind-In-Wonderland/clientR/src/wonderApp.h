#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "caller.h"

#define HOST "localhost"
#define PORT 12346


class wonderApp : public ofBaseApp {

public:

    void setup();
    void loadSettings(string fileString);
    
    void update();
    void draw();
    
    void keyPressed(int key);
    

	ofxOscReceiver  receiver;
	int port;
	
	ofVideoPlayer   movie;
	int movieWidth;
	int movieHeight;
	int movieX;
	int movieY;	
	char * movieFile;
	bool fullscreen;
    bool looping;
	
	bool started;
	
    vector<Caller*> callers;

    bool bLocal;
    bool bDebug;

    int nRows;
    float startY;
    float endY;
};

