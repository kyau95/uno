/* File:    game.cpp
 * Author:  ykevin1
 * Info:    Game object declaration file
 */

#include <random>
#include "game.h"

Game::Game() {
  deal_initial_hand();
}

Game::~Game() {
  std::cout << "First player is: " << get_first_player()->get_name() << "\n";
}

void Game::deal_initial_hand() {
  for (Player* p : m_player_list) {
    p->add_cards(m_deck.draw_cards(INITIAL_HAND_SIZE));
  }
}

Player* Game::get_first_player() const {
  std::random_device device;
  std::mt19937 rgen(device());
  // Calls in range [0-3] <- Note: inclusive not exclusive end
  std::uniform_int_distribution<int> dist(0, 3);

  return m_player_list[dist(rgen)];
}

void Game::setup() {
}

Deck Game::get_deck() const {
  return m_deck;
}

std::vector<Card*> Game::get_discard_pile() const {
  return m_discard_pile;
}

std::vector<Player*> Game::get_players() const {
  return m_player_list;
}
