#ifndef SmartTwoWayMultiSprite__H
#define SmartTwoWayMultiSprite__H
#include <string>
#include <vector>
#include <cmath>
#include "TwoWayMultiSprite.h"

class SmartTwoWayMultiSprite : public TwoWayMultiSprite {
public:
  SmartTwoWayMultiSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartTwoWayMultiSprite(const SmartTwoWayMultiSprite&);
  virtual ~SmartTwoWayMultiSprite() {}

  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }

private:
  enum MODE {NORMAL, EVADE};

  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
