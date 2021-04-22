/* File:    deck.h
 * Author:  ykevin1
 * Info:    Deck object header file
 */

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <string>
#include <vector>

class Deck {
public:
  Deck();
  ~Deck();

  // deck operations
  void shuffle();
  void replace_deck(std::vector<Card *>);
  Card *draw_card();
  std::vector<Card *> draw_cards(int);

  // getters
  std::vector<Card *> get_deck() const;
  size_t get_size() const;

  // printing
  friend std::ostream &operator<<(std::ostream &out, const Deck &rhs) {
    for (Card *c : rhs.m_cards) {
      out << *c << ' ';
    }
    out << '\n';
    return out;
  }

private:
  std::vector<Card *> m_cards;

  void build_deck();
};

#endif // DECK_H
