/* File:    game.h
 * Author:  ykevin1
 * Info:    Game object header file
 */

#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include <vector>

enum Direction { FORWARD, BACKWARD };
enum State { SETUP, PLAY, GAMEOVER, END };

class Game {
public:
  Game();
  ~Game();

  Card *peek_top_discard() const;
  void deal_initial_hand();
  Player *get_first_player();
  void setup();
  void run();

  Player *get_current_player() const;
  Deck *get_deck() const;
  std::vector<Card *> get_discard_pile() const;
  std::vector<Player *> get_players() const;

  // Print current game state
  friend std::ostream &operator<<(std::ostream &out, const Game &rhs) {
    for (Player *p : rhs.m_player_list) {
      out << *p << '\n';
    }
    return out;
  }

private:
  int m_current_index;
  Player *current_player;
  Deck *m_deck;
  std::vector<Card *> m_discard_pile;
  std::vector<Player *> m_player_list{new Player("P1"), new Player("P2"),
                                      new Player("P3"), new Player("P4")};
  Direction game_dir;

  Color valid_color;
  Rank valid_rank;

  static const size_t INITIAL_HAND_SIZE = 7;
};

#endif // GAME_H
