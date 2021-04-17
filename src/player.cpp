/* File:    player.cpp
 * Author:  ykevin1
 * Info:    Player object declaration file
 */

#include "player.h"

Player::Player(std::string name) : m_name(name) {}

Player::~Player() {
  for (Card* c : m_hand) {
    delete c;
  }
}

void Player::add_card(Card* card) {
  m_hand.push_back(card);
}

void Player::add_cards(std::vector<Card*> cards) {
  for (Card* element : cards) {
    m_hand.push_back(element);
  }
}

std::string Player::get_name() const {
  return m_name;
}

std::vector<Card*> Player::get_hand() const {
  return m_hand;
}
