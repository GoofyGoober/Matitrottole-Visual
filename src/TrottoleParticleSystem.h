//
//  TrottoleParticleSystem.h
//  trottoleVisual
//
//  Created by XXX on 09/03/16.
//
//

#ifndef __trottoleVisual__TrottoleParticleSystem__
#define __trottoleVisual__TrottoleParticleSystem__

#include "TrottoleParticleSystem.h"
#include "GoofyParticleSystem.h"

class TrottoleParticleSystem: public GoofyParticleSystem
{
public:
  TrottoleParticleSystem();
  virtual void    updateAndDraw(vector<ofVec3f> targets, bool colorWhite = false);
private:
  
};

#endif /* defined(__trottoleVisual__TrottoleParticleSystem__) */
