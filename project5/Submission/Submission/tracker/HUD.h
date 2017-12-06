#ifndef HUD__H
#define HUD__H
#include "vector2f.h"


class HUD {
public:
  static HUD& getInstance();
  void draw() const;

  bool getVisible() { return visible;}
  void setVisible(bool isVisible) {visible = isVisible;}
  void update();


private:
  int HUDWidth;
  int HUDHeight;
  Vector2f position;

  bool visible;
  bool initVis;

  HUD();
  HUD(const HUD&);
  HUD& operator=(const HUD&);
};
#endif
