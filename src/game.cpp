/* File:    game.cpp
 * Author:  ykevin1
 * Info:    Game object declaration file
 */

#include "game.h"
#include <random>
#include <unistd.h>

Game::Game() : game_state(SETUP), direction(FORWARD) {
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
  int c = 0;
  while (game_state != QUIT && c < 10) {
    std::cout << "Player " << current_player->get_name() << "'s turn!\n";
    print_top_card();
    std::cout << current_player->get_name() << "'s hand\n";
    current_player->show_hand();
    int player_card_choice = current_player->find_valid_card(peek_top_discard());
    if (player_card_choice >= 0) {
      Card *temp = current_player->play_card(player_card_choice);
      m_discard_pile.push_back(temp);
      std::cout << current_player->get_name() << " played " << *temp << "\n\n";
    }
    else {
      std::cout << current_player->get_name() << " could not play a card and must draw\n\n";
      current_player->add_card(m_deck->draw_card());
    }
    current_player = m_player_list[++m_current_index % 4];
    ++c;
    sleep(3); // make the program wait a little so the user can process the changes
  }
}

void Game::print_top_card() const {
  std::cout << "Top card is: " << *peek_top_discard() << std::endl;
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

    // In the rare chance that there were 2 or more wild cards drawn back-to-back
    for (Card *c : m_discard_pile) {
      m_deck->get_deck().push_back(m_discard_pile[0]);
      m_discard_pile.erase(m_discard_pile.begin());
    }
    m_deck->shuffle();
    deal_first_card();
  }
  else {
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
  direction = FORWARD;
  deal_initial_hand();
  current_player = get_first_player();
  deal_first_card();
  game_state = PLAY;
}

// GETTERS

Player *Game::get_current_player() const {
  return m_player_list[m_current_index];
}

Deck *Game::get_deck() const { return m_deck; }

std::vector<Card *> Game::get_discard_pile() const { return m_discard_pile; }

std::vector<Player *> Game::get_players() const { return m_player_list; }
