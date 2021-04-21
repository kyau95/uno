/* File:    deck.cpp
 * Author:  ykevin1
 * Info:    Deck object declaration file
 */

#include <random>
#include "deck.h"

Deck::Deck() {
  // Make the deck and shuffle it on the initial instantiation
  build_deck();
  shuffle();
}

Deck::~Deck() {
  for (Card* c : m_cards) {
    delete c;
  }
}

void Deck::build_deck() {
  for (Card* c : m_cards) {
    delete c;
  }
  m_cards.clear();
  for (int i = 0; i < 4; ++i) {
    Color current_color = Card::m_colors[i];

    // Create one [0] card for all colors
    m_cards.push_back(new Card(current_color, 0));
    // Create two of each numbers [1-9] for all colors
    for (int j = 1; j <= 9; ++j) {
      m_cards.push_back(new Card(current_color, j));
      m_cards.push_back(new Card(current_color, j));
    }
    // Create two of each action cards [skip, reverse, +2] for all colors
    for (int j = 1; j <= 3; ++j) {
      m_cards.push_back(new Card(current_color, Card::m_ranks[j]));
      m_cards.push_back(new Card(current_color, Card::m_ranks[j]));
    }
  }
  // Create the wild cards 
  for (int i = 0; i < 4; ++i) {
    m_cards.push_back(new Card(Color::NONE, Rank::WILD));
    m_cards.push_back(new Card(Color::NONE, Rank::WILD_FOUR));
  }
}

void Deck::shuffle() {
  std::random_device device;
  std::mt19937 rgen(device());
  std::uniform_int_distribution<int> dist(0, m_cards.size() - 1);

  for (int i = 0; i < m_cards.size(); ++i) {
    int x = dist(rgen);
    Card* temp = m_cards[i];
    m_cards[i] = m_cards[x];
    m_cards[x] = temp;
  }
}

void Deck::replace_deck(std::vector<Card*> discards) {
  m_cards = discards;
}

Card* Deck::draw_card() {
  int n = m_cards.size() - 1;
  Card* temp =  m_cards[n];
  m_cards.pop_back();
  return temp;
}

std::vector<Card*> Deck::draw_cards(int number_cards) {
  std::vector<Card*> container;
  for (int i = 0; i < number_cards; ++i) {
    int n = m_cards.size() - 1;
    Card* temp = m_cards[n];
    container.push_back(temp);
    m_cards.pop_back();
  }
  return container;
}

std::vector<Card*> Deck::get_deck() const {
  return m_cards;
}

size_t Deck::get_size() const {
  return m_cards.size();
}
