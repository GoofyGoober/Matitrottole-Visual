//
//  TrottoleParticleSystem.cpp
//  trottoleVisual
//
//  Created by XXX on 09/03/16.
//
//

#include "TrottoleParticleSystem.h"

TrottoleParticleSystem::TrottoleParticleSystem()
{
  cout << "Particle System" << endl;
}
void TrottoleParticleSystem::updateAndDraw(vector<ofVec3f> targets, bool colorWhite)
{
  // if(moveNoise)
  //   goofyPerlinNoise.update();
  
  vector<GoofyParticle*>::iterator vItr = particles.begin();
  int cont = 0;
  int totPArticles = particles.size();
  while ( vItr != particles.end() )
  {
      int mapValue =  ofMap(cont, 0, totPArticles, 0, targets.size());
      mapValue = ofClamp(mapValue, 0,2);
      if(targets[mapValue].x != -100)
          (*vItr)->followTarget(targets[mapValue]);
      else
          (*vItr)->followTarget((*vItr)->startPosition);
//    if(cont < totPArticles/6)
//      (*vItr)->followTarget(targets[0]);
//    else if(cont < (totPArticles/6) * 2)
//      (*vItr)->followTarget(targets[1]);
//    else if(cont < (totPArticles/6) * 3)
//      (*vItr)->followTarget(targets[2]);
//    else if(cont < (totPArticles/6) * 4)
//      (*vItr)->followTarget(targets[3]);
//    else if(cont < (totPArticles/6) * 5)
//      (*vItr)->followTarget(targets[4]);
//    else
//      (*vItr)->followTarget(targets[5]);
    
    applyRepulsions((*vItr));
//    applyAttraction((*vItr));
    
    ofPoint center(ofGetWidth()*.5, ofGetHeight()*.5);
    ofPoint distance = (*vItr)->position - center;
    
    (*vItr)->update();
    lastActionInsideUpdateLoop((*vItr));
    
    if (!(*vItr)->active)
    {
      delete * vItr;
      vItr = particles.erase( vItr );
    }
    else
    {
//      (*vItr)->draw();
//      if(!active) return;
      ofPushStyle();
      
      ofColor color;
      
      if(cont%4 == 0)
        color = ofColor(255,0,0, 50);
      else if(cont%3 == 0)
        color = ofColor(255/cont,0,0, 50);
      else if(cont%2 == 0)
        color = ofColor(255/cont*1.5,0,0, 50);
      else
        color = ofColor(255,255,0, 80);
      ofSetColor(color);
      if(colorWhite)
        ofSetColor(50 + ofNoise((*vItr)->id * ofGetFrameNum()*.4)*55,100);
    if((*vItr)->target != (*vItr)->startPosition)
    {
        ofSetColor(100,30);
    }
      ofDrawLine((*vItr)->position.x, (*vItr)->position.y, (*vItr)->prevPosition.x, (*vItr)->prevPosition.y);
//      ofCircle((*vItr)->position, 1);
      ofPopStyle();
      (*vItr)->prevPosition = (*vItr)->position;
      vItr++;
      cont++;
    }
    //    }
  }
  this->removeRepellers();
}