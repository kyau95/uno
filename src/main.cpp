/* File:    main.cpp
 * Author:  ykevin1
 * Info:    Main driver file. This program is meant to imitate a simple game
 *          of UNO. The goal of the program is have 4 CPUs play until the game
 *          is complete. It will print out the top card on the center pile each
 *          turn and the current player/CPU turn and move selection.
 *          It will comply to all the current rules of UNO and excludes any and
 *          all house rules.
 *          TODO: implement the game with the house rule options possible
 */

#include "game.h"

int main() {
  Game uno_game;
  uno_game.run();
  return 0;
}
