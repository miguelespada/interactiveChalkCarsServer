
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxMidi.h"


#define N_CARS 2
#define CAR_W 40
#define CAR_H 15

static float dAcc, dDec, dRot, maxV, minV, outV;

// ------------------------------------------------- a simple extended box2d circle
class Car : public ofxBox2dRect {
	
public:
    
    float direction;
    float acc;
    int midi;
    bool isOut = false;
    bool isOutBounds = false;
    bool bUp, bDown, bLeft, bRight;
    ofImage img;
    
	Car() {
		setPhysics(1, 1, 1);
        direction = 0;
        acc = 0;
        
        bUp = false;
        bDown = false;
        bRight = false;
        bLeft = false;
        
	}
	
	void draw() {
        ofSetColor(255, 255, 255);
		img.setAnchorPoint(CAR_W/2.0, CAR_H/2.0);
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		ofRotate(getRotation());
        img.draw(0, 0);
		glPopMatrix();
		
	}
    void setImage(string file){
        img.loadImage(file);
        img.resize(CAR_W, CAR_H);
    }
    
    void setMidi(int m){
        midi = m * 4;
    }
    
    void update(){
        
        ofVec2f v = getVelocity();
        
        if (bLeft) direction -= dRot;
        if (bRight) direction += dRot;
        
        if (bUp) acc += dAcc;
        if (bDown) acc -= dDec;
        
        if (acc < -minV) acc = -minV;
        if ( acc > maxV) acc = maxV;
        
        if (isOut) {
            if (acc > outV)
                acc = outV;
        }
        
        float vx = acc*cos(ofDegToRad(direction));
        float vy = acc*sin(ofDegToRad(direction));
        
        setVelocity(vx, vy);
        setRotation(direction - 180);
        
        if (isOutBounds) acc = -acc * 0.7;
        
    }
    void reset(int x, int y){
        setPosition(x, y);
        acc = 0;
        direction = 0;
    }
    void checkMidi(ofxMidiMessage& msg){
        
        bool v = false;
        if(msg.status == MIDI_NOTE_OFF)
            v = false;
        if(msg.status == MIDI_NOTE_ON)
            v = true;
        
        if(msg.pitch == (midi + 0)) bLeft = v;
        if(msg.pitch == (midi + 1)) bRight = v;
        if(msg.pitch == (midi + 2)) bUp = v;
        if(msg.pitch == (midi + 3)) bDown = v;
        
    }
};

