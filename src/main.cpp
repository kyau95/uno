#include "game.h"

int main() {
  //Game uno_game;
  //uno_game.run();
  //std::cout << uno_game;
  Deck d;
  std::cout << d << std::endl;
  Card *c = d.draw_card();
  std::cout << "Card drawn is " << *c << "\n\n";
  std::cout << d << std::endl;
  return 0;
}
