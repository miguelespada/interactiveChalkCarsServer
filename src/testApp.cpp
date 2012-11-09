#include "testApp.h"
#define CAPTURE_W 640
#define CAPTURE_H 480
#define PROCESS_W 320
#define PROCESS_H 240

//--------------------------------------------------------------
void testApp::setup(){
    
    loadSettings();
    
    colorImg.allocate(CAPTURE_W, CAPTURE_H);
	grayAcc.allocate(PROCESS_W, PROCESS_H);
    
  	individualTextureSyphonServer.setName("Interactive Chalk Cars Server");
    
    tex.allocate(PROCESS_W, PROCESS_H, GL_LUMINANCE);
    ofSetFrameRate(30);
    
    for(int i = 0; i < 255; i++)
        keys[i] = false;
    
    
    recordContext.setup();
	recordImage.setup(&recordContext);
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
    
    recordContext.update();
    recordImage.update();
    
    grayImage.setFromPixels(recordImage.ir_pixels, 640, 480);
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    // recordImage.draw();
    ofSetHexColor(0xFFFFFF);
    ofBackground(0, 40, 50);
    drawOutside();
    grayImage.resize(PROCESS_W, PROCESS_H);
    
    grayImage.brightnessContrast(brightness, contrast);
    
    if(bThreshold){
       //   grayImage.contrastStretch();
        
        cvThreshold(grayImage.getCvImage(), grayImage.getCvImage(), threshold, 255, CV_THRESH_BINARY);
        
        grayImage.dilate();
        grayImage.dilate();
        grayImage.erode();
        
        grayImage.addWeighted(grayAcc, weight);
        grayAcc = grayImage;
    }
    
    tex.loadData(grayImage.getPixels(), PROCESS_W, PROCESS_H, GL_LUMINANCE);
  
   if(bShowInput){
    grayImage.draw(0, 0);
    }

    individualTextureSyphonServer.publishTexture(&tex);
    
    if(bInfo){
        ofSetHexColor(0xFFFF00);
        char reportStr[1024];
    
        sprintf(reportStr, "[v] video settings [F] snapshot [t] threshold %3d ", threshold);
        ofDrawBitmapString(reportStr, 20, 10);
        sprintf(reportStr, "fps:%3.0f ", ofGetFrameRate());
        ofDrawBitmapString(reportStr, 20, 25);
        sprintf(reportStr, "[1] show input [2] show output [i] info [r] ROI ");
        ofDrawBitmapString(reportStr, 20, 40);
        sprintf(reportStr, "[T] Threshold on/off [b] Brightness %.2f ", brightness);
        ofDrawBitmapString(reportStr, 20, 55);
        sprintf(reportStr, "[c] Contrast %.2f [w] Fade Weight %.2f", contrast, weight);
        ofDrawBitmapString(reportStr, 20, 70);
    } 
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key > 0 && key <255)
        keys[key] = true;
    
	switch (key){
        case 357: //UP
            if(keys['b']) brightness += 0.01;
            if(keys['c']) contrast += 0.01;
            if(keys['t']) threshold += 1;
            if(keys['a']) changeThreshold += 0.5;
            if(keys['w']) weight += 0.01;
            if(keys['r']) roi.y -= 1;
            
            if(keys['7']) outSide[0].y -= 1;
            if(keys['8']) outSide[1].y -= 1;
            if(keys['9']) outSide[2].y -= 1;
            if(keys['0']) outSide[3].y -= 1;
            
            break;
            
        case 359: //Down
            if(keys['b']) brightness -= 0.01;
            if(keys['c']) contrast -= 0.01;
            if(keys['t']) threshold -= 1;
            if(keys['w']) weight -= 0.01;
            if(keys['a']) changeThreshold -= 0.5;
            
            
            if(keys['7']) outSide[0].y += 1;
            if(keys['8']) outSide[1].y += 1;
            if(keys['9']) outSide[2].y += 1;
            if(keys['0']) outSide[3].y += 1;
            
            if(keys['r']) roi.y += 1;
            break;
        case 358: //RIGHT
            if(keys['r']) roi.x += 1;
            
            if(keys['7']) outSide[0].x += 1;
            if(keys['8']) outSide[1].x += 1;
            if(keys['9']) outSide[2].x += 1;
            if(keys['0']) outSide[3].x += 1;
            break;
        case 356: //LEFT
            if(keys['r']) roi.x -= 1;
            
            
            if(keys['7']) outSide[0].x -= 1;
            if(keys['8']) outSide[1].x -= 1;
            if(keys['9']) outSide[2].x -= 1;
            if(keys['0']) outSide[3].x -= 1;
            break;
            
        case '-':
            if(keys['r']){
                roiW -= 4;
                roiH -= 3;
            }
            break;
        case '+':
            if(keys['r']){
                roiW += 4;
                roiH += 3;
            }
            break;
            
        case 'F':
            saveBackground();
            break;
        case 'R':
            resetOutsideConers();
            break;
        case 'v':
            vidGrabber.videoSettings();
            break;
        case 'T':
            bThreshold = !bThreshold;
            break;
        case 's':
            saveSettings();
            break;
        case 'l':
            loadSettings();
            break;
        case 'i':
            bInfo = !bInfo;
            break;
        case '1':
            bShowInput = !bShowInput;
            break;
        case '2':
            bShowOutput = !bShowOutput;
            break;
	}
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key > 0 && key <255)
        keys[key] = false;
    }

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}

void testApp::loadSettings(){
    
    if( XML.loadFile("mySettings.xml") ){
		cout << "mySettings.xml loaded!" <<endl;
	}else{
		cout <<  "unable to load mySettings.xml check data/ folder" << endl;
	}
    
    XML.pushTag("SETTINGS");
    threshold	= XML.getValue("THRESHOLD", 170);
    bThreshold = XML.getValue("bTHRESOLD", 0);
    weight = XML.getValue("WEIGHT", 0.1);
    brightness = XML.getValue("BRIGHTNESS", 0.0);
    contrast = XML.getValue("CONTRAST", 0.0);
    changeThreshold = XML.getValue("CHANGETHRESHOLD", 5);
    bInfo = XML.getValue("bINFO", 1);
    bShowInput = XML.getValue("bSHOWINPUT", 1);
    bShowOutput = XML.getValue("bSHOWOUTPUT", 1);
    XML.popTag();
    
    XML.pushTag("ROI");
    roi.x = XML.getValue("X", 50);
    roi.y = XML.getValue("Y", 50);
    roiW  = XML.getValue("WIDTH", 400);
    roiH = XML.getValue("HEIGHT", 300);
    XML.popTag();
    
    XML.pushTag("OUTSIDE");
    for(int i = 0; i < 4; i++){
        XML.pushTag("PT", i);
        outSide[i].x = XML.getValue("X", 0);
        outSide[i].y = XML.getValue("Y", 0);
        XML.popTag();
    }
    XML.popTag();

    cout << "Settings loaded" << endl;
    
}

//--------------------------------------------------------------
void testApp::saveSettings(){
    XML.clear();
    XML.setValue("SETTINGS:THRESHOLD", threshold);
    XML.setValue("SETTINGS:bTHRESHOLD", bThreshold);
    
    XML.setValue("SETTINGS:WEIGHT", weight);
    XML.setValue("SETTINGS:BRIGHTNESS", brightness);
    XML.setValue("SETTINGS:CONTRAST", contrast);
    XML.setValue("SETTINGS:CHANGETHRESHOLD", changeThreshold);
    XML.setValue("SETTINGS:bSHOWINPUT", bShowInput);
    XML.setValue("SETTINGS:bSHOWOUTPUT", bShowOutput);
    XML.setValue("SETTINGS:bINFO", bInfo);
    
    XML.addTag("ROI");
    XML.pushTag("ROI");
    XML.setValue("X", roi.x);
    XML.setValue("Y", roi.y);
    XML.setValue("WIDTH", roiW);
    XML.setValue("HEIGHT", roiH);
    XML.popTag();
    
    
    XML.addTag("OUTSIDE");
    XML.pushTag("OUTSIDE");
    for(int i = 0; i < 4; i++){
        XML.addTag("PT");
        XML.pushTag("PT", i);
        XML.setValue("X", outSide[i].x,i);
        XML.setValue("Y", outSide[i].y,i);
        XML.popTag();
    }
    XML.popTag();
    
    XML.saveFile("mySettings.xml");
    cout << "Settings saved" << endl;
}
void testApp::saveBackground(){
    ofPixels p;
    p.setFromPixels(colorImg.getPixels(), CAPTURE_W, CAPTURE_H, 3);
    ofSaveImage(p, "background.png");
    cout << "Background saved" << endl;
}
//--------------------------------------------------------------
void testApp::drawOutside(){
    
    int nPts = 4;
    int c = 0;
    int outputW = CAPTURE_W;
    int outputH = CAPTURE_H;
    
    CvPoint* pts = new CvPoint[nPts];
    
    pts[0].x = 0;
    pts[0].y = 0;
    pts[1].x = outputW - 1;
    pts[1].y = 0;
    pts[2].x = outSide[1].x;
    pts[2].y = outSide[1].y;
    pts[3].x = outSide[0].x;
    pts[3].y = outSide[0].y;
    
    cvFillPoly( grayImage.getCvImage(), &pts, &nPts, 1,
               CV_RGB(c,c,c) );
    
    pts[0].x = 0;
    pts[0].y = 0;
    pts[1].x = outSide[0].x;
    pts[1].y = outSide[0].y;
    
    pts[2].x = outSide[3].x;
    pts[2].y = outSide[3].y;
    
    pts[3].x = 0;
    pts[3].y = outputH - 1;
    
    cvFillPoly( grayImage.getCvImage(), &pts, &nPts, 1,
               CV_RGB(c,c,c) );
    
    
    pts[0].x = outputW - 1;
    pts[0].y = 0;
    pts[1].x = outputW - 1;
    pts[1].y = outputH - 1;
    pts[2].x = outSide[2].x;
    pts[2].y = outSide[2].y;
    pts[3].x = outSide[1].x;
    pts[3].y = outSide[1].y;
    
    cvFillPoly( grayImage.getCvImage(), &pts, &nPts, 1,
               CV_RGB(c,c,c) );
    
    
    pts[0].x = outputW - 1;
    pts[0].y = outputH - 1;
    pts[1].x = 0;
    pts[1].y = outputH - 1;
    pts[2].x = outSide[3].x;
    pts[2].y = outSide[3].y;
    pts[3].x = outSide[2].x;
    pts[3].y = outSide[2].y;
    
    cvFillPoly( grayImage.getCvImage(), &pts, &nPts, 1,
               CV_RGB(c,c,c) );
    
}
void testApp::resetOutsideConers(){
    outSide[0] = ofPoint(0,0);
    outSide[1] = ofPoint(CAPTURE_W-1,0);
    outSide[2] = ofPoint(CAPTURE_W-1,CAPTURE_H-1);
    outSide[3] = ofPoint(0,CAPTURE_H-1);
    
}
