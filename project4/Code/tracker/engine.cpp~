#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "player.h"
#include "TwoWayMultiSprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"


Engine::~Engine() { 
  delete player;
  for(Drawable* step:spriteList){
    delete step;
  }
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  world2("back2", Gamedata::getInstance().getXmlInt("back2/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("Naruto")),
  hud( HUD::getInstance() ),
  strategies(),
  currentStrategy(1),
  collision(false),
  currentSprite(0),
  makeVideo( false )
{
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  Jiraya = new SmartTwoWayMultiSprite("SmartJiraya", pos, w, h);
  player->attach(Jiraya);
  spriteList.push_back(Jiraya);

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();
  world2.draw();

  for(auto step: spriteList){
  step->draw();
  }
  strategies[currentStrategy]->draw();
  if ( collision ) {
    IOmod::getInstance().writeText("Oops: Collision", 10, 90);
  }
  player->draw();
  viewport.draw();
  hud.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  player->update(ticks);
  for(auto step: spriteList){
    step->update(ticks);
  }
  world.update();
  world2.update();
  if(clock.getTicks() > 3000) hud.update();
  viewport.update(); // always update viewport last
}

/*
void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 3;
  if ( currentSprite == 0 ) {
    Viewport::getInstance().setObjectToTrack(Naruto);
  }
  else if ( currentSprite == 1) {
    Viewport::getInstance().setObjectToTrack(Jiraya);
  }
  else {
    Viewport::getInstance().setObjectToTrack(Toad);
  }
}
*/

void Engine::checkForCollisions() {
  collision = false;
  for ( const Drawable* d : spriteList ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          //switchSprite();
        }
        if (keystate[SDL_SCANCODE_F1]) {
          hud.setVisible(!(hud.getVisible()));
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        player->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
