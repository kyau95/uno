/* File:    card.cpp
 * Author:  ykevin1
 * Info:    Card object declaration file
 */

#include "card.h"

const Color Card::m_colors[]{RED, GREEN, BLUE, YELLOW, NONE};
const Rank Card::m_ranks[]{NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_FOUR};
const std::string Card::m_color_strings[]{
    "\033[31mRED\033[32m\033[0m", "\033[32mGREEN\033[37m\033[0m",
    "\033[34mBLUE\033[37m\033[0m", "\033[33mYELLOW\033[37m\033[0m",
    "\033[1mWILD\033[37m\033[0m"};

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
  return m_color == rhs.m_color &&
         (m_rank == rhs.m_rank || (m_rank == NUMBER && rhs.m_rank == NUMBER &&
                                   m_number == rhs.m_number));
}

bool Card::operator!=(const Card &rhs) {
  return m_color != rhs.m_color || m_rank != rhs.m_rank ||
         m_number != rhs.m_number;
}

bool Card::is_number_card() const {
  return m_rank == NUMBER;
}

bool Card::is_action_card() const {
  return m_rank != NUMBER;
}

bool Card::is_wild_card() const {
  return m_color == NONE;
}

// GETTERS

const Color Card::get_color() const { return m_color; }

const Rank Card::get_rank() const { return m_rank; }

const int Card::get_number() const { return m_number; }
