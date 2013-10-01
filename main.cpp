#include "CrocGame.h"
#include <iostream>
#include "Crawler.cpp"

int main() {
  bool noob = false;
  CrocSession s(L"Group 2", noob);
  Crawler crawler(&s);
  crawler.play();
  std::cout << "Hello World" << std::endl;
}
