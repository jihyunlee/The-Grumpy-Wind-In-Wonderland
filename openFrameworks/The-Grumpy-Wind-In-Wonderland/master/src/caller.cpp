//
//  caller.cpp
//  BigScreensMasterPlayer
//
//  Created by Jihyun Lee on 2/10/13.
//  Copyright (c) 2013 NYU ITP. All rights reserved.
//

#include <iostream>
#include "caller.h"

Caller::Caller(string id_, string phoneNumber_) {
    
    id = id_;
    phoneNumber = phoneNumber_;

    img0.loadImage("c0.png");
    img1.loadImage("c1.png");
    img2.loadImage("c2.png");
    img3.loadImage("c3.png");
    img4.loadImage("c4.png");
    img5.loadImage("c5.png");
    img6.loadImage("c6.png");
    img7.loadImage("c7.png");
    img8.loadImage("c8.png");
    img9.loadImage("c9.png");
    img0.loadImage("c0.png");
    imgX.loadImage("cX.png");
    imgDash.loadImage("cDash.png");

    fontWidth = 34;
    fontHeight = 44;
}

Caller::~Caller() {
    
}

bool Caller::isCaller(string id_) {
    bool ret = id.compare(id_);
    return !ret;
}

void Caller::draw(float x, float y) {

    string s = phoneNumber.substr(0,3) + "-xxx-" + phoneNumber.substr(6,10);
        
    int margin = 1;
    float startX = x;
        
    for(int i=0; i<s.size(); i++) {
        ofPushMatrix();

        float r = ofRandom(1);
        if(r > 0.95) ofRotate(ofRandom(-0.2,0.2));
                
        char c = s.at(i);
        if(c == '0')      img0.draw(x, y, fontWidth, fontHeight);
        else if(c == '1') img1.draw(x, y, fontWidth, fontHeight);
        else if(c == '2') img2.draw(x, y, fontWidth, fontHeight);
        else if(c == '3') img3.draw(x, y, fontWidth, fontHeight);
        else if(c == '4') img4.draw(x, y, fontWidth, fontHeight);
        else if(c == '5') img5.draw(x, y, fontWidth, fontHeight);
        else if(c == '6') img6.draw(x, y, fontWidth, fontHeight);
        else if(c == '7') img7.draw(x, y, fontWidth, fontHeight);
        else if(c == '8') img8.draw(x, y, fontWidth, fontHeight);
        else if(c == '9') img9.draw(x, y, fontWidth, fontHeight);
        else if(c == 'x') imgX.draw(x, y, fontWidth, fontHeight);
        else if(c == '-') imgDash.draw(x, y, fontWidth, fontHeight);
        ofPopMatrix();
            
        x += fontWidth + margin;
    }
}
