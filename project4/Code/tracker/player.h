#ifndef PLAYER__H
#define PLAYER__H

#include <string>
#include <list>
#include <cmath>
#include "TwoWayMultiSprite.h"
#include "SmartTwoWayMultiSprite.h"

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void attach( SmartTwoWayMultiSprite* o ) { observers.push_back(o); } 
  void detach( SmartTwoWayMultiSprite* o );

  std::list<SmartTwoWayMultiSprite*> observers;

  void right();
  void left();
  void up();
  void down();
  void stop();
private:
  bool collision;
  Vector2f initialVelocity;
};
#endif
