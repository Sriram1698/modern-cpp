#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  string player_name_;
  std::cout << "Enter your name: ";
  std::cin >> player_name_;

  if (std::cin.fail()) {
    std::cerr << "Players name cannot be empty" << std::endl;
    return EXIT_FAILURE;
  }
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, std::move(player_name_));
  game.Run(controller, renderer, kMsPerFrame);

  return EXIT_SUCCESS;
}