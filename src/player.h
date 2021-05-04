/* File:    player.h
 * Author:  ykevin1
 * Info:    Player object header file
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <string>
#include <vector>

class Player {
public:
  Player(std::string name);
  ~Player();

  Player(const Player &rhs);
  Player &operator=(const Player &rhs);

  void add_card(Card *card);
  void add_cards(std::vector<Card *> cards);
  void clear_hand();
  Color find_optimal_color();
  int find_valid_card(Card *current_card);
  Card *play_card(int pos);
  void show_hand() const;

  bool has_uno() const;
  bool has_empty_hand() const;

  // Getters
  std::string get_name() const;
  std::vector<Card *> get_hand() const;

  // Print information of player
  friend std::ostream &operator<<(std::ostream &out, const Player &rhs) {
    out << "Player: " << rhs.m_name << " has " << rhs.m_hand.size()
        << " cards left\n";
    out << "Cards: ";
    for (Card *c : rhs.m_hand) {
      out << *c << ' ';
    }
    return out;
  }

private:
  std::string m_name;
  std::vector<Card *> m_hand;
};

#endif // PLAYER_H
