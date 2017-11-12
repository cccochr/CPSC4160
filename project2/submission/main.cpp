#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "circle.h"
#include "rectangle.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 480;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(
    WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer
  );

  //Background
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  //Rectangle1
  SDL_Point rectangle1_origin = {0, 0};
  SDL_Color rectangle1_color = {50,50,100,50};
  int rectangle1_height = WINDOW_HEIGHT, rectangle1_width = WINDOW_WIDTH;
  Rectangle rectangle1(rectangle1_origin, rectangle1_width, rectangle1_height, rectangle1_color);
  rectangle1.drawRectangle(renderer);

  //Revolve Line
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
  SDL_RenderDrawLine(renderer, 0, 240, 1280, 240);

  //Sun
  SDL_Point sunCenter = {-100, 240};
  SDL_Color sunColor = {255,255,0,255};
  int sunRadius = 450;
  Circle sun(sunRadius, sunCenter, sunColor);
  sun.drawCircle(renderer);

  //Mercury
  SDL_Point mercuryCenter = {400, 240};
  SDL_Color mercuryColor = {200,200,200,255};
  int mercuryRadius = 10;
  Circle mercury(mercuryRadius, mercuryCenter, mercuryColor);
  mercury.drawCircle(renderer);

  //Venus
  SDL_Point venusCenter = {450, 240};
  SDL_Color venusColor = {225,200,100,255};
  int venusRadius = 15;
  Circle venus(venusRadius, venusCenter, venusColor);
  venus.drawCircle(renderer);

  //Earth
  SDL_Point earthCenter = {510, 240};
  SDL_Color earthColor = {100,255,100,255};
  int earthRadius = 20;
  Circle earth(earthRadius, earthCenter, earthColor);
  earth.drawCircle(renderer);

  //Earth2
  SDL_Point earth2Center = {510, 240};
  SDL_Color earth2Color = {100,100,255,255};
  int earth2Radius = 15;
  Circle earth2(earth2Radius, earth2Center, earth2Color);
  earth2.drawCircle(renderer);

  //Earth3
  SDL_Point earth3Center = {510, 240};
  SDL_Color earth3Color = {100,255,100,255};
  int earth3Radius = 10;
  Circle earth3(earth3Radius, earth3Center, earth3Color);
  earth3.drawCircle(renderer);

  //Moon
  SDL_Point moonCenter = {510, 210};
  SDL_Color moonColor = {200,200,200,255};
  int moonRadius = 5;
  Circle moon(moonRadius, moonCenter, moonColor);
  moon.drawCircle(renderer);

  //Mars
  SDL_Point marsCenter = {575, 240};
  SDL_Color marsColor = {255,150,100,255};
  int marsRadius = 18;
  Circle mars(marsRadius, marsCenter, marsColor);
  mars.drawCircle(renderer);

  //Asteroid Field
  SDL_SetRenderDrawColor(renderer, 255, 255, 230, 100);
  
  for(int x = 650; x < 700; x+=2){
    for(int y = 0; y < 480; y+=3){
      if(!(std::rand()%9))
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
  

  //Jupiter
  SDL_Point jupiterCenter = {860, 240};
  SDL_Color jupiterColor = {250,200,50,255};
  int jupiterRadius = 75;
  Circle jupiter(jupiterRadius, jupiterCenter, jupiterColor);
  jupiter.drawCircle(renderer);

  //Saturn
  SDL_Point saturnCenter = {1010, 240};
  SDL_Color saturnColor = {250,250,100,255};
  int saturnRadius = 50;
  Circle saturn(saturnRadius, saturnCenter, saturnColor);
  saturn.drawCircle(renderer);

  //Uranus
  SDL_Point uranusCenter = {1115, 240};
  SDL_Color uranusColor = {200,200,255,255};
  int uranusRadius = 35;
  Circle uranus(uranusRadius, uranusCenter, uranusColor);
  uranus.drawCircle(renderer);

  //Neptune
  SDL_Point neptuneCenter = {1200, 240};
  SDL_Color neptuneColor = {125,125,255,255};
  int neptuneRadius = 30;
  Circle neptune(neptuneRadius, neptuneCenter, neptuneColor);
  neptune.drawCircle(renderer);

  //Pluto??
  SDL_Point plutoCenter = {1260, 225};
  SDL_Color plutoColor = {200,200,200,255};
  int plutoRadius = 8;
  Circle pluto(plutoRadius, plutoCenter, plutoColor);
  pluto.drawCircle(renderer);

  //Frame
  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WINDOW_WIDTH, WINDOW_HEIGHT, 
    "cccochr");
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
