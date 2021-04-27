/* File:    player.cpp
 * Author:  ykevin1
 * Info:    Player object declaration file
 */

#include "player.h"

Player::Player(std::string name) : m_name(name) {}

Player::~Player() { clear_hand(); }

Player::Player(const Player &rhs) {
  m_name = rhs.m_name;
  m_hand = rhs.m_hand;
}

Player &Player::operator=(const Player &rhs) {
  // No self-assignment
  if (this != &rhs) {
    m_name = rhs.m_name;
    m_hand = rhs.m_hand;
  }
  return *this;
}

void Player::add_card(Card *card) {
  // Just add one singular card, no biggie
  m_hand.push_back(card);
}

void Player::add_cards(std::vector<Card *> cards) {
  // Adding multiple cards, no biggie
  for (Card *element : cards) {
    m_hand.push_back(element);
  }
}

void Player::clear_hand() {
  for (Card *card : m_hand) {
    delete card;
  }
  m_hand.clear();
}

bool Player::has_uno() const { return m_hand.size() == 1; }

bool Player::has_empty_hand() const { return m_hand.empty(); }

// GETTERS

std::string Player::get_name() const { return m_name; }

std::vector<Card *> Player::get_hand() const { return m_hand; }
