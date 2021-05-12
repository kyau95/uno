/* File:    card.cpp
 * Author:  ykevin1
 * Info:    Card object declaration file
 */

#include "card.h"

const Color Card::_colors[]{RED, GREEN, BLUE, YELLOW, NONE};
const Rank Card::_ranks[]{NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_FOUR};
const std::string Card::_color_strings[]{
    "\033[31mRED\033[32m\033[0m", "\033[32mGREEN\033[37m\033[0m",
    "\033[34mBLUE\033[37m\033[0m", "\033[33mYELLOW\033[37m\033[0m",
    "\033[1mWILD\033[37m\033[0m"};

Card::Card(Color color, Rank rank)
    : _color(color), _rank(rank), _number(-1) {}

Card::Card(Color color, int number)
    : _color(color), _rank(NUMBER), _number(number) {}

Card::Card(Color color, Rank rank, int number)
    : _color(color), _rank(rank), _number(number) {}

Card::~Card() {}

bool Card::operator==(const Card &rhs) {
  // Only valid for exactly the same card, matching color and rank
  // Useful for implementing in the jump-in feature BUT not right now
  return _color == rhs._color &&
         (_rank == rhs._rank || (_rank == NUMBER && rhs._rank == NUMBER &&
                                   _number == rhs._number));
}

bool Card::operator!=(const Card &rhs) {
  return _color != rhs._color || _rank != rhs._rank ||
         _number != rhs._number;
}

bool Card::is_number_card() const { return _rank == NUMBER; }

bool Card::is_action_card() const { return _rank != NUMBER; }

bool Card::is_wild_card() const { return _color == NONE; }

// GETTERS

const Color Card::get_color() const { return _color; }

const Rank Card::get_rank() const { return _rank; }

const int Card::get_number() const { return _number; }
