#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "SmartTwoWayMultiSprite.h"
#include "viewport.h"
#include "HUD.h"
#include "collisionStrategy.h"

class Player;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void play();
  //void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  World world2;
  Viewport& viewport;

  SmartTwoWayMultiSprite* Jiraya;

  Player* player;

  HUD& hud;
  
  std::vector<Drawable*> spriteList;  
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
