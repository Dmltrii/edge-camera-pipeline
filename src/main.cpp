#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "frame_stats.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }
  std::ifstream file(argv[1]);

  if (!file) {
    return 1;
  }

  int x;
  std::vector<int> frame;
  while (file >> x) {
    frame.push_back(x);
    // x — очередное число
  }

  auto result = compute_stats(frame);
  if (result == std::nullopt) {
    return 1;
  } else {
    std::cout << *result << '\n';
  }

  return 0;
}
