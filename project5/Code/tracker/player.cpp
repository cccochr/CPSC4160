#include "player.h"
#include "gamedata.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(),
  collision(false),
  initialVelocity(getVelocity()),
  originalY(0),
  jumping(0),
  jumpHeight(Gamedata::getInstance().getXmlInt(name+"/jumpHeight"))
{ }

Player::Player(const Player& s) :
  TwoWayMultiSprite(s), 
  observers(s.observers),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  originalY(s.originalY),
  jumping(s.jumping),
  jumpHeight(Gamedata::getInstance().getXmlInt(name+"/jumpHeight"))
  { }

Player& Player::operator=(const Player& s) {
  TwoWayMultiSprite::operator=(s);
  collision = s.collision;
  observers = s.observers;
  initialVelocity = s.initialVelocity;
  originalY = s.originalY;
  jumping = s.jumping;
  jumpHeight = Gamedata::getInstance().getXmlInt(name+"/jumpHeight");
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

// New Code for Jump
void Player::jump()  {
    if(jumping) return;
    if(channelMovement) return;
    originalY = getY();
    channelMovement = -1;
    jumping = 1;
    std::cout << "jumping" << std::endl;
}
// New Code for Jump


void Player::update(Uint32 ticks) {

    //up jump
    if (jumping == 1){
      std::cout << "jumping up" << std::endl;
      int currentY = getY();
      if(getVelocityY() == 0)  setVelocityY(-1000);
      if(currentY <= originalY - jumpHeight) jumping = 2;
    }
    else if (jumping == 2){
      std::cout << "jumping down" << std::endl;
      setVelocityY(1000);
      int currentY = getY();
      if(currentY >= originalY){
        std::cout << "jumping break" << std::endl;
        setVelocityY(0);
        setY(originalY);
        jumping = 0; 
        channelMovement = 0;     
      }
    }
    
    
    //while (currentY <= originalY - jumpHeight){
    //  currentY = currentY + jumpHeight; //iinc // updating.....
    //}
    //while ( currentY >= originalY){
    //currentY = currentY - jumpHeight; //ddec // updating...
    //}
    
//jump code here
  TwoWayMultiSprite::update(ticks);

  if ( !collision ){ 
  std::list<SmartTwoWayMultiSprite*>::iterator ptr = observers.begin();
    while ( ptr != observers.end() ) {
      (*ptr)->setPlayerPos( getPosition() );
      (*ptr)->setPlayerChannel( currentChannel );
      ++ptr;
    }

  //Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  //setPosition(getPosition() + incr);

  stop();
  }
  else{ // death animation
  stop();
  }
}

