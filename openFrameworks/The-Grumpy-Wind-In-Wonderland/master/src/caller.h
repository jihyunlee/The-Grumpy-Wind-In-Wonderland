//
//  caller.h
//  BigScreensMasterPlayer
//
//  Created by Jihyun Lee on 2/10/13.
//  Copyright (c) 2013 NYU ITP. All rights reserved.
//

#ifndef BigScreensMasterPlayer_caller_h
#define BigScreensMasterPlayer_caller_h

#pragma once
#include "ofMain.h"


class Caller : public ofBaseApp {
    
public:
    
    Caller(string id_, string phoneNumber_);
    ~Caller();
    
    void draw(float x, float y);

    bool isCaller(string id_);

    
    string id;
    string phoneNumber;

    ofImage img0;
    ofImage img1;
    ofImage img2;
    ofImage img3;
    ofImage img4;
    ofImage img5;
    ofImage img6;
    ofImage img7;
    ofImage img8;
    ofImage img9;
    ofImage imgX;
    ofImage imgDash;
    
    int fontWidth;
    int fontHeight;
    
};

#endif
