#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player {
public:
  Player(const string &&name, const int prev_high_score = -1);
  void operator=(const Player& player);
  ~Player();

  int score() const;
  int prevHighScore() const;
  const string &name() const;

  void updateScore(const int score);
  void printSummary() const;

private:

  int prev_high_score_;
  string name_;
  int current_score_;
};

#endif