/* File:    deck.cpp
 * Author:  ykevin1
 * Info:    Deck object declaration file
 */

#include "deck.h"
#include <random>

Deck::Deck() {
  // Make the deck and shuffle it on the initial instantiation
  build_deck();
  shuffle();
}

Deck::~Deck() { clear_deck(); }

// Build the entire deck of UNO cards
void Deck::build_deck() {
  _cards.clear();
  for (int i = 0; i < 4; ++i) {
    Color current_color = Card::_colors[i];

    // Create one [0] card for all colors
    _cards.push_back(new Card(current_color, 0));

    // Create two of each numbers [1-9] for all colors
    for (int j = 1; j <= 9; ++j) {
      _cards.push_back(new Card(current_color, j));
      _cards.push_back(new Card(current_color, j));
    }

    // Create two of each action cards [skip, reverse, +2] for all colors
    for (int j = 1; j <= 3; ++j) {
      _cards.push_back(new Card(current_color, Card::_ranks[j]));
      _cards.push_back(new Card(current_color, Card::_ranks[j]));
    }
  }
  // Create the wild cards
  for (int i = 0; i < 4; ++i) {
    _cards.push_back(new Card(Color::NONE, Rank::WILD));
    _cards.push_back(new Card(Color::NONE, Rank::WILD_FOUR));
  }
}

void Deck::shuffle() {
  // Random generator shuffles only within the current deck size
  // Reasoning cause when replacing the deck, it is not always the full 108
  // cards
  std::random_device device;
  std::mt19937 r_gen(device());
  std::uniform_int_distribution<int> dist(0, _cards.size() - 1);

  for (int i = 0; i < _cards.size(); ++i) {
    int x = dist(r_gen);
    Card *temp = _cards[i];
    _cards[i] = _cards[x];
    _cards[x] = temp;
  }
}

void Deck::replace_deck(std::vector<Card *> discards) {
  // Checking for self-allocation
  if (_cards == discards) {
    throw std::logic_error("Invalid deck argument, Attempted self-allocation");
  }
  _cards = discards;
}

Card *Deck::draw_card() {
  // Draw from empty deck bad, should have already replaced the deck
  if (_cards.empty()) {
    throw std::invalid_argument("Cannot draw from empty deck");
  }

  // end() points to nullptr, - 1 is the final non-null element in vector
  Card *temp = *(_cards.end() - 1);
  _cards.pop_back();
  return temp;
}

std::vector<Card *> Deck::draw_cards(int number_cards) {
  // Not enough cards in deck bad, should have already replaced the deck
  if (_cards.size() < number_cards) {
    throw std::invalid_argument("Not enough cards to draw from deck");
  }

  // TODO: Maybe could just pass the current hand vector in?
  // Or keep as is, dunno yet
  std::vector<Card *> container;
  for (int i = 0; i < number_cards; ++i) {
    int n = _cards.size() - 1;
    Card *temp = _cards[n];
    container.push_back(temp);
    _cards.pop_back();
  }
  return container;
}

void Deck::clear_deck() {
  for (Card *c : _cards) {
    delete c;
  }
}

// GETTERS

std::vector<Card *> Deck::get_deck() const { return _cards; }

size_t Deck::get_size() const { return _cards.size(); }
