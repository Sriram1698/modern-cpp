#include "game.h"
#include "SDL.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           const string &&player_name)
    : snake_(grid_width, grid_height), engine(dev()),
      player_(std::move(readFromFile(std::move(player_name)))),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)), food_selection_(0, 2) {

  populateColors();
  populateFoodVarities();
  PlaceFood();
}

Game::~Game() {
  std::cout << "\nGame has terminated successfully!\n";
  if (foodCycleThread_.joinable()) {
    foodCycleThread_.join();
  }
  printSummary();
  saveScore();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running_ = true;

  // Start the food cycle thread
  foodCycleThread_ = std::thread(&Game::foodCycle, this);

  while (running_) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running_, snake_);
    Update();
    const auto &position = food_->position();
    const auto &color = color_defs_.colors_[food_->color()];
    renderer.Render(snake_, position, color.r(), color.g(), color.b());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(player_.name(), player_.score(),
                                 player_.prevHighScore(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::foodCycle() {
  while (running_) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Lock to get the access to food without any race or
    // simultaneous modifications on food
    if (food_->isExpired() || food_->isConsumed()) {
      PlaceFood();
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  int rand_food = food_selection_(engine);
  food_ = food_varities_[rand_food];
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake_.SnakeCell(x, y)) {
      food_->setPosition(x, y);
      food_->reset();
      return;
    }
  }
}

void Game::Update() {
  if (!snake_.alive) {
    return;
  }

  snake_.Update();

  int new_x = static_cast<int>(snake_.head_x);
  int new_y = static_cast<int>(snake_.head_y);

  // Check if there's food over here
  // Lock to get the access to food without any race or
  // simultaneous modifications on food
  std::lock_guard<std::mutex> lock(mutex_);
  const auto &position = food_->position();
  if (position.x == new_x && position.y == new_y) {
    updateScore();
    // Grow snake and increase speed.
    updateBody();
    updateSpeed();
    // Set the food to be consumed
    food_->foodConsumed();
  }
}

void Game::updateSpeed() {
  if (food_->foodType() != FoodType::NO_SPEED_INCREASE_FOOD) {
    snake_.speed += 0.02;
  }
}

void Game::updateBody() {
  if (food_->foodType() != FoodType::DOUBLE_INCREMENT_WITHOUT_GROWING_FOOD) {
    snake_.GrowBody();
  }
}

void Game::updateScore() {
  if (food_->foodType() == FoodType::DOUBLE_INCREMENT_WITHOUT_GROWING_FOOD) {
    player_.updateScore(player_.score() + 2);
  } else {
    player_.updateScore(player_.score() + 1);
  }
}

Player Game::readFromFile(const string &&player_name) {
  std::ifstream file(Game::FILE_PATH);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      string name;
      int score;
      iss >> name >> score;
      if (name.compare(player_name) == 0) {
        return Player(std::move(player_name), score);
      }
    }
    file.close();
  }
  return Player(std::move(player_name));
}

void Game::saveScore() {
  const int prev_high_score = player_.prevHighScore();
  const int current_score = player_.score();
  if ((current_score > prev_high_score)) {
    std::ifstream file_read(Game::FILE_PATH);
    bool player_already_exists = false;
    std::ostringstream tmp_strm;

    if (file_read.is_open()) {
      string line;

      while (std::getline(file_read, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        iss >> name >> score;

        // Check if the agent already exist,
        // If so, then update the high score
        // Do not change other player's high score if there is/are any
        if (name.compare(player_.name()) == 0) {
          player_already_exists = true;
          tmp_strm << player_.name() << " " << player_.score() << "\n";
        } else {
          tmp_strm << line << "\n";
        }
      }
      file_read.close();
    }

    // If the player was not found in the file, then append the player
    if (!player_already_exists) {
      tmp_strm << player_.name() << " " << player_.score() << "\n";
    }

    std::ofstream file_write(FILE_PATH);
    if (file_write.is_open()) {
      file_write << tmp_strm.str();
      file_write.close();
    } else {
      std::cerr << "Unable to save the file" << std::endl;
    }
  }
}

void Game::populateColors() {
  color_defs_.colors_.insert({Colors::RED, Color(255, 0, 0)});
  color_defs_.colors_.insert({Colors::GREEN, Color(0, 255, 0)});
  color_defs_.colors_.insert({Colors::BLUE, Color(0, 0, 255)});
  color_defs_.colors_.insert({Colors::CYAN, Color(0, 255, 255)});
  color_defs_.colors_.insert({Colors::PURPLE, Color(128, 0, 128)});
  color_defs_.colors_.insert({Colors::YELLOW, Color(255, 255, 0)});
}

void Game::populateFoodVarities() {
  SDL_Point init_food_position_;
  init_food_position_.x = 0.;
  init_food_position_.y = 0.;
  food_varities_.emplace_back(std::make_shared<Food>(
      FoodType::NORMAL_FOOD, init_food_position_, Colors::YELLOW, 10.));
  food_varities_.emplace_back(
      std::make_shared<Food>(FoodType::DOUBLE_INCREMENT_WITHOUT_GROWING_FOOD,
                             init_food_position_, Colors::GREEN, 3.));
  food_varities_.emplace_back(
      std::make_shared<Food>(FoodType::NO_SPEED_INCREASE_FOOD,
                             init_food_position_, Colors::PURPLE, 5.));
}

int Game::GetScore() const { return player_.score(); }
int Game::GetSize() const { return snake_.size; }

void Game::printSummary() const {
  std::cout << "\n";
  std::cout << "################################################" << std::endl;
  std::cout << "                  Game Summary                  " << std::endl;
  std::cout << "\n";
  std::cout << "Snake Length: \t\t" << snake_.size << std::endl;
  player_.printSummary();
  std::cout << "################################################" << std::endl;
}