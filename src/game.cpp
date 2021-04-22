/* File:    game.cpp
 * Author:  ykevin1
 * Info:    Game object declaration file
 */

#include "game.h"
#include <random>

Game::Game() { setup(); }

Game::~Game() {
  for (Player *p : m_player_list) {
    delete p;
  }
  for (Card *c : m_discard_pile) {
    delete c;
  }
}

void Game::deal_initial_hand() {
  for (Player *p : m_player_list) {
    p->add_cards(m_deck->draw_cards(INITIAL_HAND_SIZE));
  }
}

Player *Game::get_first_player() {
  std::random_device device;
  std::mt19937 r_gen(device());

  // Calls in range [0-3] <- Note: inclusive not exclusive end
  std::uniform_int_distribution<int> dist(0, 3);
  m_current_index = dist(r_gen);
  return m_player_list[m_current_index];
}

void Game::setup() {
  deal_initial_hand();
  current_player = get_current_player();
  std::cout << "First player is: " << current_player->get_name() << std::endl;
}

void Game::run() {

}

// GETTERS

Player *Game::get_current_player() const {
  return m_player_list[m_current_index];
}

Deck *Game::get_deck() const { return m_deck; }

std::vector<Card *> Game::get_discard_pile() const { return m_discard_pile; }

std::vector<Player *> Game::get_players() const { return m_player_list; }
