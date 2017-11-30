#include "SmartTwoWayMultiSprite.h"
#include "gamedata.h"
#include "renderContext.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}
void SmartTwoWayMultiSprite::goLeft()  { setVelocityX( -abs(getVelocityX()) ); turnLeft(); }
void SmartTwoWayMultiSprite::goRight() { setVelocityX( fabs(getVelocityX()) ); turnRight(); }
void SmartTwoWayMultiSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartTwoWayMultiSprite::goDown()  { setVelocityY( fabs(getVelocityY()) );  }

SmartTwoWayMultiSprite::SmartTwoWayMultiSprite(const std::string& name, const Vector2f& pos, 
  int w, int h) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance"))
{}

SmartTwoWayMultiSprite::SmartTwoWayMultiSprite(const SmartTwoWayMultiSprite& s) : 
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance)
{}
void SmartTwoWayMultiSprite::update(Uint32 ticks) { 
  TwoWayMultiSprite::update(ticks);
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = EVADE;
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }

}
