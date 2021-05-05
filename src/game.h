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
enum State { SETUP, PLAY, GAMEOVER, QUIT };

class Game {
public:
  Game();
  ~Game();

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
  int m_current_index = -1;
  Player *current_player = nullptr;
  Deck *m_deck = nullptr;
  std::vector<Card *> m_discard_pile;
  std::vector<Player *> m_player_list{new Player("P1"), new Player("P2"),
                                      new Player("P3"), new Player("P4")};
  Direction m_direction;
  State m_game_state;
  Color m_valid_color;
  Rank m_valid_rank;
  int m_valid_number;

  static const size_t INITIAL_HAND_SIZE = 7;

  void activate_card_effect();
  void deal_first_card();
  void deal_initial_hand();
  Card *draw_until_valid_card(Player *current_player, Card *top_card);
  Player *get_first_player();
  Card *peek_top_discard() const;
  void print_discard_pile() const;
  void print_top_card() const;
  void reset_game();
  void setup();
  void show_player_hand() const;
  void wild_card_change_color(Color optimal_color);
};

#endif // GAME_H
