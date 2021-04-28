/* File:    game.cpp
 * Author:  ykevin1
 * Info:    Game object declaration file
 */

#include "game.h"
#include <random>

Game::Game() : game_state(SETUP), direction(FORWARD) {
  current_player = get_first_player();
  m_deck = new Deck();
}

Game::~Game() {
  for (Player *p : m_player_list)
    delete p;
  for (Card *c : m_discard_pile)
    delete c;
  delete m_deck;
}

void Game::run() {
  setup();
  while (game_state != QUIT) {
    game_state = QUIT;
  }
}

void Game::print_discard_pile() const {
  for (Card *card : m_discard_pile)
    std::cout << *card << ' ';
  std::cout << '\n';
}

void Game::deal_first_card() {
  // Deals the first card of the game and sets the valid color and valid rank
  // Recurses until the card is not a wild card
  m_discard_pile.push_back(m_deck->draw_card());
  if (peek_top_discard()->get_color() == NONE) {
    // std::cout << "First card was a WILD card! Trying again!\n";
    deal_first_card();
  }
  else {
    // print_discard_pile();
    valid_color = peek_top_discard()->get_color();
    valid_rank = peek_top_discard()->get_rank();
  }
}

Card *Game::peek_top_discard() const {
  return m_discard_pile[m_discard_pile.size() - 1];
}

void Game::deal_initial_hand() {
  for (Player *p : m_player_list)
    p->add_cards(m_deck->draw_cards(INITIAL_HAND_SIZE));
}

Player *Game::get_first_player() {
  std::random_device device;
  std::mt19937 r_gen(device());

  // Calls in range [0-3] <- Note: inclusive not exclusive end
  std::uniform_int_distribution<int> dist(0, 3);
  m_current_index = dist(r_gen);
  return m_player_list[m_current_index];
}

void Game::reset_game() {
  for (Card *card : m_discard_pile)
    delete card;
  m_discard_pile.clear();
  for (Player *player : m_player_list)
    player->clear_hand();
  m_player_list.clear();
  m_player_list = {new Player("P1"), new Player("P2"), new Player("P3"),
                   new Player("P4")};
  delete m_deck;
  m_deck = new Deck();
  direction = FORWARD;
  game_state = SETUP;
}

void Game::setup() {
  /* STUFF THAT HAPPENS BEFORE FOR THE GAME EVEN STARTS
   * Hands are dealt to all players (7 cards each)
   * TODO: A top card is drawn (must not be a wild card)
   * The first player is chosen
   * Direction is set to FORWARD
   * Game state switches to PLAY phase
   */
  deal_initial_hand();
  current_player = get_first_player();
  deal_first_card();
  std::cout << "Top card is: " << *peek_top_discard() << std::endl;
  std::cout << "Player " << current_player->get_name() << "'s turn!\n";
}

// GETTERS

Player *Game::get_current_player() const {
  return m_player_list[m_current_index];
}

Deck *Game::get_deck() const { return m_deck; }

std::vector<Card *> Game::get_discard_pile() const { return m_discard_pile; }

std::vector<Player *> Game::get_players() const { return m_player_list; }
