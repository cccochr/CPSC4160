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
void SmartTwoWayMultiSprite::goUp()    { up(); }
void SmartTwoWayMultiSprite::goDown()  { down(); }

SmartTwoWayMultiSprite::SmartTwoWayMultiSprite(const std::string& name, const Vector2f& pos, 
  int w, int h) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  playerChannel(1),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance"))
{}

SmartTwoWayMultiSprite::SmartTwoWayMultiSprite(const SmartTwoWayMultiSprite& s) : 
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  playerChannel(s.playerChannel),
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
    //std::cout << "normal" << std::endl;
    if(currentChannel == playerChannel){  if(distanceToEnemy <= safeDistance) currentMode = EVADE;}
  }
  else if  ( currentMode == EVADE ) {

    //std::cout << "evade" << std::endl;
    if( (currentChannel != playerChannel) || (distanceToEnemy > safeDistance)) currentMode=NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( currentChannel == playerChannel ) {
        //std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        if(rand()%2 == 0){ 
          if(currentChannel != 3){
          up();}
        }
        else{ 
          if(currentChannel != 1){
          down();}  
        }      
        //std::cout << currentChannel << std::endl;
      }

    }
  }

}
