#include <sstream>
#include "HUD.h"
#include "gamedata.h"
#include "ioMod.h"
#include "clock.h"


HUD& HUD::getInstance() {
  static HUD hud;
  return hud;
}

HUD::HUD() : 
  HUDWidth(Gamedata::getInstance().getXmlInt("HUD/width")),
  HUDHeight(Gamedata::getInstance().getXmlInt("HUD/height")),
  position(Gamedata::getInstance().getXmlInt("HUD/X"), Gamedata::getInstance().getXmlInt("HUD/Y")), 
  visible(false),
  initVis(true)
{}

void HUD::update(){
  initVis = false;
}

void HUD::draw() const {
  if(visible || initVis){
    IOmod::getInstance().writeText("Move around with WASD", position[0], position[1]);
    //IOmod::getInstance().writeText(fpsString, position[0], position[1]);
    //IOmod::getInstance().writeText(fpsString, position[0], position[1]);
    //IOmod::getInstance().writeText(fpsString, position[0], position[1]);
    const std::string fpsString = "FPS: " + std::to_string(Clock::getInstance().getFps());
    IOmod::getInstance().writeText(fpsString, position[0], position[1]+50);
  }
}

