/* File:    card.h
 * Author:  ykevin1
 * Info:    Card object header file
 */

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

enum Color { RED, GREEN, BLUE, YELLOW, NONE };

enum Rank { NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_FOUR };

class Card {
public:
  // Constructor for non-numeric cards (reverse, skip, wild, +2, +4)
  Card(Color color, Rank rank);

  // Constructor for number cards (0 - 9)
  Card(Color color, int number);

  // Explicitly construct the entire card, don't know if needed, but it exists
  Card(Color color, Rank rank, int number);
  ~Card();

  // Equality operators
  bool operator==(const Card &rhs);
  bool operator!=(const Card &rhs);

  // Getters
  const Color get_color() const;
  const Rank get_rank() const;
  const int get_number() const;

  friend std::ostream &operator<<(std::ostream &out, const Card &rhs) {
    switch (rhs.m_color) {
    case RED:
      out << "\033[31m";
      break;
    case GREEN:
      out << "\033[32m";
      break;
    case YELLOW:
      out << "\033[33m";
      break;
    case BLUE:
      out << "\033[34m";
      break;
    case NONE:
      out << "\033[1m";
      break;
    }
    switch (rhs.m_rank) {
    case NUMBER:
      out << rhs.m_number;
      break;
    case SKIP:
      out << "S";
      break;
    case REVERSE:
      out << "R";
      break;
    case DRAW_TWO:
      out << "+2";
      break;
    case WILD:
      out << "W";
      break;
    case WILD_FOUR:
      out << "W4";
      break;
    }
    out << "\033[37m\033[0m";
    return out;
  }

  static const Color m_colors[];
  static const Rank m_ranks[];

private:
  Color m_color;
  Rank m_rank;
  int m_number;
};

#endif // CARD_H
