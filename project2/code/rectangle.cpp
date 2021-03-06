#include <iostream>
#include <sstream>
#include <iomanip>
#include "rectangle.h"

void Rectangle::drawRectangle (SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, myColor.r, myColor.g, myColor.b, myColor.a);
    SDL_RenderFillRect(renderer, &myRectangle);
}

std::ostream& operator<<(std::ostream& out, const Rectangle& rect) {
  out << "This is a rectangle.";
  return out;
}
