#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "TwoWayMultiSprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  for(auto step:spriteList){
    delete step;
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
  Toad(new Sprite("Toad")),
  Naruto(new TwoWayMultiSprite("Naruto")),
  Jiraya(new MultiSprite("Jiraya")),
  currentSprite(0),
  makeVideo( false )
{
  spriteList.push_back(Toad),
  spriteList.push_back(Naruto),
  spriteList.push_back(Jiraya),
  Viewport::getInstance().setObjectToTrack(Naruto);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();
  world2.draw();

  for(auto step: spriteList){
  step->draw();
  }

  //Toad->draw();
  //Naruto->draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto step: spriteList){
  step->update(ticks);
  }
  //Toad->update(ticks);
  //Naruto->update(ticks);
  world.update();
  world2.update();
  viewport.update(); // always update viewport last
}

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
          switchSprite();
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
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
