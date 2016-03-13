#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetWindowShape(1920, 1080);
  ofSetWindowPosition(3000, 0);
  ofToggleFullscreen();
  ofBackground(0); // sfondo nero
  for(int a = 0; a < 6 * 500; a++)
  {
    GoofyParticle* tempParticle = particleSystem.addParticle(ofVec3f(ofRandomWidth(), ofRandomHeight(),0), ofRandom(5, 10), 0);
    tempParticle->friction = ofRandom(.31, .9400);
    tempParticle->spring = ofRandom(.161, .5900);
    tempParticle = NULL;
    
  }
//  targets.push_back(ofVec2f(0,0));
  fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F_ARB);
  fbo.begin();
  ofClear(0, 255);
  fbo.end();
  ofSetBackgroundAuto(false);
  
  gui.setup();
  gui.add(clean.set("Clean", false));
  
  receiver.setup(12346);
  
  
  targets.push_back(ofVec2f(0,0));
  targets.push_back(ofVec2f(0,0));
  targets.push_back(ofVec2f(0,0));
    
    actives.push_back(false);
    actives.push_back(false);
    actives.push_back(false);
    
    
    offsetTargets.push_back(ofVec2f(0,0));
    offsetTargets.push_back(ofVec2f(0,0));
    offsetTargets.push_back(ofVec2f(0,0));
    
    
    angles.push_back(ofRandom(PI));
    angles.push_back(ofRandom(PI));
    angles.push_back(ofRandom(PI));
    
    timers.push_back(0);
    timers.push_back(0);
    timers.push_back(0);
//  targets.push_back(ofVec2f());
//  targets.push_back(ofVec2f());
//  targets.push_back(ofVec2f());
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  
//  "blob_0" x y 1
  
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(m);
    string title = m.getAddress();
    string id = ofSplitString(title, "_")[1];
    cout << "Receive = " << title << " "  << id << endl;
    cout << "x = " << m.getArgAsInt(0) << endl;
    cout << "y = " << m.getArgAsInt(1) << endl;
//    targets[ofToInt(id)].x = float(m.getArgAsInt(0)/100.0) * ofGetWindowWidth();
//    targets[ofToInt(id)].y = float((m.getArgAsInt(1))/100.0) * ofGetWindowHeight();
      int newId = ofToInt(id);
      cout << "UD ) " << newId << endl;
      if(newId == 6) // blu id = 6
        newId = 0;
      else if(newId == 2) // Rosso id = 2
          newId = 1;
      else if(newId == 5)           // Verde id = 5
          newId = 2;
      cout << "UD ) 2 ))>" << newId << endl;
      //      newId = newId%3;
//      if(newId > 2)
      //          newId = 2;
      timers[newId]+= 25;
      actives[newId] == true;
      targets[newId].x = float(m.getArgAsInt(0)/100.0) * ofGetWindowWidth();
      targets[newId].y = float((m.getArgAsInt(1))/100.0) * ofGetWindowHeight();
    cout << targets[newId] << endl;
  }
    
    if(actives[0] && actives[1] && actives[2])
    {
        
    }
    else if(actives[0] || actives[1] || actives[2])
    {
        if(!actives[0])
        {
            if(actives[1])
                targets[0] = targets[1];
            if(actives[2])
                targets[0] = targets[2];
        }
        if(!actives[1])
        {
            if(actives[0])
                targets[1] = targets[0];
            if(actives[2])
                targets[1] = targets[2];
        }
        if(!actives[2])
        {
            if(actives[0])
                targets[2] = targets[0];
            if(actives[1])
                targets[2] = targets[1];
        }
    }
  
    
    vector<ofVec3f> tempTargets;
    
    for(int a = 0; a < timers.size(); a++)
    {
        angles[a] += 10;
        float radiusSize = ofNoise(ofGetFrameNum()*.5 * a, ofGetFrameNum() * .006);
        offsetTargets[a].x = cos(angles[a]) * radiusSize;
        offsetTargets[a].y = sin(angles[a]) * radiusSize;
        timers[a]--;
        timers[a] = ofClamp(timers[a], 0, 100);
        if(timers[a] == 0)
        {
            if(!actives[0] && !actives[1] && !actives[2])
            {
                targets[a].x = -100;
                targets[a].y = -100;
            }
            actives[a] == false;
        }
        else
        {
        }
//        tempTargets.push_back(targets[a] +offsetTargets[a]);
        
    }
  
  fbo.begin();
  ofSetColor(255);
  GoofyMagneticPoint* repeller;
//  repeller = new GoofyMagneticPoint(targets[0], 30, 35, true);
//  particleSystem.addRepeller(repeller);
//  repeller = NULL;
  particleSystem.updateAndDraw(targets, !clean);
//  if(clean)
//  {
    ofSetColor(0,2);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//  }
  if(ofGetFrameNum() == 10 || ofGetFrameNum() == 50)
    ofClear(0,255);
  fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(255);
  fbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
  if(drawGUI)
  {
    gui.draw();
  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if(key == 'g')
    drawGUI = !drawGUI;
  if(key == 'c')
  {
    fbo.begin();
    ofClear(0,255);
    fbo.end();
  }
  if(key == 'f')
  {
    ofToggleFullscreen();
  }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
