#include <string>
#include <iostream>
#include <SDL.h>

class Rectangle {
public:
  Rectangle(SDL_Point origin, int w, int h, SDL_Color color) :
  myColor(color),
  myRectangle()
  {
    myRectangle.x = origin.x;
    myRectangle.y = origin.y;
    myRectangle.h = h;
    myRectangle.w = w;
  }
  void drawRectangle (SDL_Renderer* renderer);
private:
  const SDL_Color myColor;
  SDL_Rect myRectangle;
  Rectangle(const Rectangle&);

};

  std::ostream& operator<<(std::ostream&, const Rectangle&);
