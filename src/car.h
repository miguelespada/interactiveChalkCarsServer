//
//  car.h
//  interactiveChalkCars
//
//  Created by miguel valero espada on 10/30/12.
//
//
#include "ofMain.h"

#ifndef __interactiveChalkCars__car__
#define __interactiveChalkCars__car__

#include <iostream>

#endif /* defined(__interactiveChalkCars__car__) */

class car{
    
    public:
        ofImage texture;
        ofPoint position;
        float direction;
        int w, h;
    car(){};
    
    car(string s, int ww, int hh){
        w = ww;
        h = hh;
       texture.loadImage(s);
        texture.resize(w, h);
        position = ofPoint(0, 0);
        direction = 0;

    };
    void draw(){
        texture.setAnchorPoint(w/2.0, h/2.0);
        
        ofSetHexColor(0xffffff);
        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofRotateZ(direction + 90);
        texture.draw(0, 0);
        ofPopMatrix();
        
    }

};