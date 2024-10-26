#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "player.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include <random>
#include <unordered_map>
#include <vector>

using std::shared_ptr;
using std::unordered_map;
using std::vector;

///////////////////////////////////////////////
// Colors
// Define the structure for color
struct Color {
public:
  Color() : r_(255), g_(255), b_(0) {}
  Color(const uint8_t r, const uint8_t g, const uint8_t b)
      : r_(r), g_(g), b_(b) {}

  uint8_t r() const { return r_; }
  uint8_t g() const { return g_; }
  uint8_t b() const { return b_; }

private:
  const uint8_t r_, g_, b_;
};

// Define multiple colors
enum Colors { RED, GREEN, BLUE, CYAN, PURPLE, YELLOW };

struct ColorDefs {
  unordered_map<Colors, Color> colors_;
};

///////////////////////////////////////////////

// Food
// Define the type of food
enum FoodType {
  NORMAL_FOOD,
  NO_SPEED_INCREASE_FOOD,
  DOUBLE_INCREMENT_WITHOUT_GROWING_FOOD
};

class Food {
public:
  Food(const FoodType food_type, const SDL_Point &position, const Colors color)
      : food_type_(food_type), position_(position), color_(color) {}

  void operator=(const Food &food) {
    food_type_ = food.food_type_;
    color_ = food.color_;
    position_.x = food.position_.x;
    position_.y = food.position_.y;
  }

  void setPosition(const float &x, const float y) {
    position_.x = x;
    position_.y = y;
  }

  FoodType foodType() const { return food_type_; }
  Colors color() const { return color_; }
  const SDL_Point &position() const { return position_; }

private:
  FoodType food_type_;
  Colors color_;
  SDL_Point position_;
};

///////////////////////////////////////////////

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height,
       const string &&player_name);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void printSummary() const;

private:
  Snake snake_;
  Player player_;
  shared_ptr<Food> food_;
  inline static const string FILE_PATH = "../data/scores.txt";

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> food_selection_;

  vector<shared_ptr<Food>> food_varities_;
  ColorDefs color_defs_;

  void PlaceFood();
  void Update();

  void updateSpeed();
  void updateBody();
  void updateScore();

  Player readFromFile(const string &&player_name);
  void saveScore();

  void populateColors();
  void populateFoodVarities();
};

#endif