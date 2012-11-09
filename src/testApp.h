#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "ofxXmlSettings.h"
#include "ofxOpenNI.h"


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
    void drawOutside();
    
    
        ofVideoGrabber 		vidGrabber;
        
        ofxCvColorImage			colorImg;
        ofxCvColorImage			backImg;
        ofxCvGrayscaleImage 	grayImage, grayAcc;
        ofxXmlSettings XML;
    
        ofxSyphonServer mainOutputSyphonServer;
    
    
        ofTexture tex;
    
        ofxSyphonServer individualTextureSyphonServer;
  
    
    
    ofPoint outSide[4];
    
    bool isOut(int x, int y);
    bool isOutBounds(int x, int y);

    
    int  threshold;
    float changeThreshold;
    
    bool keys[255];
    bool bBackground, bThreshold, bInfo;
    float weight;
    float brightness, contrast;
    
    bool bShowInput, bShowOutput;
    
    ofPoint roi;
    int roiW, roiH;
    void resetOutsideConers();
    
	ofxOpenNIContext	recordContext;
	ofxIRGenerator		recordImage;
};

