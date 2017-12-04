#include "player.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(),
  collision(false),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  TwoWayMultiSprite(s), 
  observers(s.observers),
  collision(s.collision),
  initialVelocity(s.getVelocity())
  { }

Player& Player::operator=(const Player& s) {
  TwoWayMultiSprite::operator=(s);
  collision = s.collision;
  observers = s.observers;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::detach( SmartTwoWayMultiSprite* o ) {
  std::list<SmartTwoWayMultiSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
    turnRight();
  }
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
    turnLeft();
  }
} 


//void Player::up()    { 
//  if ( getY() > 265) {
//    setVelocityY( -initialVelocity[1] );
//  }
//} 
//void Player::down()  { 
//  if ( getY() < worldHeight-getScaledHeight()) {
//    setVelocityY( initialVelocity[1] );
//  }
//}



// New Code for Jump
void Player::jump()  {
  //if ( getY() > 270)
  //{
     //setVelocityY(-initialVelocity[1]);
     //std::cout <<"JUMP"<< std::endl;
  //}
   
}
// New Code for Jump

void Player::update(Uint32 ticks) {

  TwoWayMultiSprite::update(ticks);

  if ( !collision ){ 
  std::list<SmartTwoWayMultiSprite*>::iterator ptr = observers.begin();
    while ( ptr != observers.end() ) {
      (*ptr)->setPlayerPos( getPosition() );
      (*ptr)->setPlayerChannel( currentChannel );
      ++ptr;
    }

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  stop();
  }
  else{ // death animation
  stop();
  }
}

