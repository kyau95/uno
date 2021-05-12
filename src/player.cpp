/* File:    player.cpp
 * Author:  ykevin1
 * Info:    Player object declaration file
 */

#include "player.h"

Player::Player(std::string name) : _name(name) {}

Player::~Player() { clear_hand(); }

Player::Player(const Player &rhs) {
  _name = rhs._name;
  _hand = rhs._hand;
}

Player &Player::operator=(const Player &rhs) {
  // No self-assignment
  if (this != &rhs) {
    _name = rhs._name;
    _hand = rhs._hand;
  }
  return *this;
}

void Player::add_card(Card *card) {
  // Just add one singular card, no biggie
  _hand.push_back(card);
}

void Player::add_cards(std::vector<Card *> cards) {
  // Adding multiple cards, no biggie
  for (Card *element : cards) {
    _hand.push_back(element);
  }
}

void Player::clear_hand() {
  for (Card *card : _hand) {
    delete card;
  }
  _hand.clear();
}

Color Player::find_optimal_color() {
  // frequency order is RED, GREEN, BLUE, YELLOW
  int color_freq[4]{0};
  for (Card *card : _hand) {
    ++color_freq[card->get_color()];
  }
  int most_freq = color_freq[0];
  int color_index = 0;
  for (int i = 1; i < 4; ++i) {
    if (color_freq[i] > most_freq) {
      most_freq = color_freq[i];
      color_index = i;
    }
  }
  return Card::_colors[color_index];
}

int Player::find_valid_card(Card *current_card) {
  // Return the first valid card found in the hand
  for (int i = 0; i < _hand.size(); ++i) {
    Card *active = _hand[i];
    // Check for Wild cards first
    if (active->get_color() == NONE) {
      return i;
    }
    // Check for matching colors
    else if (active->get_color() == current_card->get_color()) {
      return i;
    }
    // Top card is a number card, looking for matching number
    else if (active->get_rank() == NUMBER == current_card->get_rank() == NUMBER) {
      if (current_card->get_number() == active->get_number()) {
        return i;
      }
    }
    else if (active->get_rank() == current_card->get_rank()) {
      return i;
    }
  }
  // Indicates no matching cards in hand and player will need to draw
  return -1;
}

Card *Player::play_card(int pos) {
  Card *temp = _hand[pos];
  _hand.erase(_hand.begin() + pos);
  return temp;
}

void Player::show_hand() const {
  for (Card *card : _hand)
    std::cout << *card << ' ';
  std::cout << std::endl;
}

bool Player::has_uno() const { return _hand.size() == 1; }

bool Player::has_empty_hand() const { return _hand.empty(); }

// GETTERS

std::string Player::get_name() const { return _name; }

std::vector<Card *> Player::get_hand() const { return _hand; }
