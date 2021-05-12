/* File:    game.cpp
 * Author:  ykevin1
 * Info:    Game object declaration file
 */

#include "game.h"
#include <random>
#include <unistd.h>

Game::Game() : _game_state(SETUP), _direction(FORWARD) { _deck = new Deck(); }

Game::~Game() {
  for (Player *p : _player_list)
    delete p;
  for (Card *c : _discard_pile)
    delete c;
  delete _deck;
}

void Game::run() {
  setup();
  while (_game_state != GAMEOVER) {
    show_game_details();
    int player_card_choice =
        _current_player->find_valid_card(peek_top_discard());
    Card *temp;
    if (player_card_choice < 0) {
      std::cout << _current_player->get_name()
                << " could not play a card and must draw\n\n";
      temp = draw_until_valid_card(_current_player, peek_top_discard());
    } else {
      temp = _current_player->play_card(player_card_choice);
    }
    std::cout << _current_player->get_name() << " played " << *temp << "\n\n";
    _discard_pile.push_back(temp);

    if (temp->is_action_card() || temp->is_wild_card()) {
      activate_action_effect(peek_top_discard());
    }

    if (_current_player->has_uno()) {
      std::cout << _current_player->get_name() << " declares UNO!\n\n";
    } else if (_current_player->has_empty_hand()) {
      declare_winner();
    }
    advance_next_player();
    usleep(1500000); // make the program wait a little so the user can process
                     // the changes
  }
}

void Game::activate_action_effect(Card *top_card) {
  // TODO: Something broke here, most likely in the DRAW_TWO and WILD_FOUR
  // section in regards to drawing additonal cards
  Rank rank = top_card->get_rank();
  if (rank == SKIP) {
    advance_next_player();
  } else if (rank == REVERSE) {
    // Flip the bit 1 -> 0 or 0 -> 1, need to cast back to enum type
    _direction = static_cast<Direction>(_direction ^ 1);
  } else if (rank == DRAW_TWO) {
    _current_player->add_cards(_deck->draw_cards(2));
    advance_next_player();
  } else if (rank == WILD) {
    activate_wild_effect(peek_top_discard());
  } else {
    activate_action_effect(peek_top_discard());
    //_current_player->add_cards(_deck->draw_cards(4));
    // advance_next_player();
  }
}

void Game::activate_wild_effect(Card *top_card) {
  Color color_change = _current_player->find_optimal_color();
  _valid_color = color_change;
  std::cout << "Color has changed to " << Card::_color_strings[color_change]
            << "\n\n";
}

void Game::advance_next_player() {
  switch (_direction) {
  case FORWARD:
    _current_player = _player_list[++_current_index % 4];
    break;
  case BACKWARD:
    _current_player = _player_list[--_current_index % 4];
    break;
  default:
    break;
  }
}

void Game::deal_first_card() {
  // Deals the first card of the game and sets the valid color and valid rank
  // Recurses until the card is not a wild card
  _discard_pile.push_back(_deck->draw_card());
  if (peek_top_discard()->get_color() == NONE) {
    // Rare chance that there were 2 or more wild cards drawn back-to-back
    for (Card *c : _discard_pile) {
      _deck->get_deck().push_back(_discard_pile[0]);
      _discard_pile.erase(_discard_pile.begin());
    }
    _deck->shuffle();
    deal_first_card();
  } else {
    _valid_color = peek_top_discard()->get_color();
    _valid_rank = peek_top_discard()->get_rank();
  }
}

void Game::deal_initial_hand() {
  for (Player *p : _player_list)
    p->add_cards(_deck->draw_cards(INITIAL_HAND_SIZE));
}

void Game::declare_winner() {
  std::cout << _current_player->get_name() << " has won the game of UNO!\n\n";
  _game_state = GAMEOVER;
}

Card *Game::draw_until_valid_card(Player *_current_player, Card *top_card) {
  // Player will continue to draw cards from the deck until it matches the
  // top card in either color/number/action or if the card is wild
  Card *check;
  int card_counter = 0;
  do {
    if (_deck->get_deck().empty()) {
      std::cout << "Draw deck is empty, replacing cards and shuffling\n\n";
      _deck->replace_deck(_discard_pile);
      _discard_pile.clear();
      _deck->shuffle();
    }
    check = _deck->draw_card();
    _current_player->add_card(check);
    ++card_counter;
  } while (check->get_color() != _valid_color);
  std::cout << _current_player->get_name() << " drew " << card_counter
            << " cards\n";
  return check;
}

Player *Game::get_first_player() {
  std::random_device device;
  std::mt19937 r_gen(device());

  // Calls in range [0-3] <- Note: inclusive not exclusive end
  std::uniform_int_distribution<int> dist(0, 3);
  _current_index = dist(r_gen);
  return _player_list[_current_index];
}

void Game::print_discard_pile() const {
  for (Card *card : _discard_pile) {
    std::cout << *card << ' ';
  }
  std::cout << '\n';
}

void Game::print_top_card() const {
  std::cout << "Top card is: " << *peek_top_discard() << std::endl;
}

Card *Game::peek_top_discard() const {
  return _discard_pile[_discard_pile.size() - 1];
}

void Game::reset_game() {
  for (Card *card : _discard_pile) {
    delete card;
  }
  _discard_pile.clear();
  for (Player *player : _player_list) {
    player->clear_hand();
  }
  _player_list.clear();
  _player_list = {new Player("P1"), new Player("P2"), new Player("P3"),
                  new Player("P4")};
  delete _deck;
  _deck = new Deck();
  _direction = FORWARD;
  _game_state = SETUP;
}

void Game::setup() {
  /* STUFF THAT HAPPENS BEFORE FOR THE GAME EVEN STARTS
   * Hands are dealt to all players (7 cards each)
   * TODO: A top card is drawn (must not be a wild card)
   * The first player is chosen
   * Direction is set to FORWARD
   * Game state switches to PLAY phase
   */
  _direction = FORWARD;
  deal_initial_hand();
  _current_player = get_first_player();
  deal_first_card();
  _game_state = PLAY;
}

void Game::show_game_details() const {
  std::cout << "It's " << _current_player->get_name() << "'s turn!\n";
  print_top_card();
  std::cout << _current_player->get_name() << "'s hand\n";
  _current_player->show_hand();
}

void Game::wild_card_change_color(Color optimal_color) {}

// GETTERS

Player *Game::get_current_player() const {
  return _player_list[_current_index];
}

Deck *Game::get_deck() const { return _deck; }

std::vector<Card *> Game::get_discard_pile() const { return _discard_pile; }

std::vector<Player *> Game::get_players() const { return _player_list; }
