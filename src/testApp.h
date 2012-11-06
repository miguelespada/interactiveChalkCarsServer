#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "ofxXmlSettings.h"


class testApp : public ofBaseApp{
        
    public:
        void setup();
        void update();
        void draw();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
        void saveSettings();
        void loadSettings();
        void saveBackground();
    
    
        ofVideoGrabber 		vidGrabber;
        
        ofxCvColorImage			colorImg;
        ofxCvColorImage			backImg;
        ofxCvGrayscaleImage 	grayImage, grayAcc;
        ofxXmlSettings XML;
    
        ofxSyphonServer mainOutputSyphonServer;
    
    
        ofTexture tex;
    
<<<<<<< HEAD
        ofxSyphonServer individualTextureSyphonServer;
=======
  
    
    
    ofxBox2d box2d;
    Car cars[N_CARS];
    ofPoint outSide[4];
    void drawOutside();
    bool isOut(int x, int y);
    bool isOutBounds(int x, int y);

    
	void newMidiMessage(ofxMidiMessage& eventArgs);
	stringstream text;
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
>>>>>>> parent of e45c8b2... KIKK festival
    
    
    int  threshold;
    float changeThreshold;
    
    bool keys[255];
    bool bBackground, bThreshold, bInfo;
    float weight;
    float brightness, contrast;
    
    bool bShowInput, bShowOutput;
    
    ofPoint roi;
    int roiW, roiH;
};

