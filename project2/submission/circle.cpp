#include <iostream>
#include <sstream>
#include <iomanip>
#include "circle.h"

void Circle::drawCircle (SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, myColor.r, myColor.g, myColor.b, myColor.a);
  for (int w = 0; w < myRadius * 2; w++) {
    for (int h = 0; h < myRadius * 2; h++) {
      int dx = myRadius - w; // horizontal offset
      int dy = myRadius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (myRadius * myRadius)) {
        SDL_RenderDrawPoint(renderer, myCenter.x + dx, myCenter.y + dy);
      }
    }
  }
}

std::ostream& operator<<(std::ostream& out, const Circle& circle) {
  out << "This is a circle.";
  return out;
}

