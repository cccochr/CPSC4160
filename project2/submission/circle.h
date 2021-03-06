#include <string>
#include <iostream>
#include <SDL.h>

class Circle {
public:
  Circle(int radi, SDL_Point center, SDL_Color color) :
  myRadius(radi), 
  myCenter(center), 
  myColor(color)
{}
  void drawCircle(SDL_Renderer* renderer);
private:
  const int myRadius;
  const SDL_Point myCenter;
  const SDL_Color myColor;
  Circle(const Circle&);

};

  std::ostream& operator<<(std::ostream&, const Circle&);
