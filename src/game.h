/* File:    game.h
 * Author:  ykevin1
 * Info:    Game object header file
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "deck.h"
#include "player.h"

enum Direction {
  FORWARD, BACKWARD
};

class Game {
public:
  Game();
  ~Game();

  void deal_initial_hand();
  Player* get_first_player();
  Player* get_current_player() const;
  void setup();
  void run();

  Deck get_deck() const;
  std::vector<Card*> get_discard_pile() const;
  std::vector<Player*> get_players() const;

  // Print current game state
  friend std::ostream& operator<<(std::ostream& out, const Game& rhs) {
    for (Player* p : rhs.m_player_list) {
      out << *p << '\n';
    }
    return out;
  }

private:
  int m_current_index;
  Deck m_deck;
  std::vector<Card*> m_discard_pile;
  std::vector<Player*> m_player_list{
   new Player("P1"), new Player("P2"), new Player("P3"), new Player("P4")
  };
  Direction game_dir;

  static const size_t INITIAL_HAND_SIZE = 7;

};

#endif // GAME_H
