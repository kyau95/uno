/* File:    card.cpp
 * Author:  ykevin1
 * Info:    Card object declaration file
 */

#include "card.h"

const Color Card::m_colors[]{RED, GREEN, BLUE, YELLOW, NONE};
const Rank Card::m_ranks[]{NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_FOUR};

Card::Card(Color color, Rank rank)
    : m_color(color), m_rank(rank), m_number(-1) {}

Card::Card(Color color, int number)
    : m_color(color), m_rank(NUMBER), m_number(number) {}

Card::Card(Color color, Rank rank, int number)
    : m_color(color), m_rank(rank), m_number(number) {}

Card::~Card() {}

bool Card::operator==(const Card &rhs) {
  // Only valid for exactly the same card, matching color and rank
  // Useful for implementing in the jump-in feature BUT not right now
  return m_color == rhs.m_color && m_rank == rhs.m_rank;
}

bool Card::operator!=(const Card &rhs) {
  return m_color != rhs.m_color && m_rank != rhs.m_rank;
}

// GETTERS

const Color Card::get_color() const { return m_color; }

const Rank Card::get_rank() const { return m_rank; }
