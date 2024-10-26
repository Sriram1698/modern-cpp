#include "player.h"
#include <iostream>

Player::Player(const string &&name, const int prev_high_score)
    : name_(std::move(name)), prev_high_score_(prev_high_score),
      current_score_(0) {}

// Move assignment operator
void Player::operator=(const Player &player) {
  name_ = std::move(player.name_);
  prev_high_score_ = player.prev_high_score_;
  current_score_ = player.current_score_;
}

Player::~Player() {}

int Player::score() const { return current_score_; }
int Player::prevHighScore() const { return std::max(0, prev_high_score_); }
const string &Player::name() const { return name_; }

void Player::updateScore(const int score) { current_score_ = score; }

void Player::printSummary() const {
  std::cout << "***********************************" << std::endl;
  std::cout << "           Player Summary          " << std::endl;
  std::cout << "\n";
  std::cout << "Name: \t\t" << name_ << std::endl;
  std::cout << "Score: \t\t" << current_score_ << std::endl;
  std::cout << "Previous high score: " << std::max(0, prev_high_score_)
            << std::endl;
  if ((current_score_ > 0) && (current_score_ > prev_high_score_)) {
    std::cout << "\n";
    std::cout << "\t     Congradulations" << std::endl;
    std::cout << "\tA new high score achieved!" << std::endl;
    std::cout << "\n";
  }
  std::cout << "***********************************" << std::endl;
}