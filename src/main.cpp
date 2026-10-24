#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "frame_stats.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }
  std::ifstream file(argv[1]);

  if (!file) {
    std::cerr << "cannot open " << argv[1] << '\n';
    return 1;
  }

  int x{};
  std::vector<int> frame;
  while (file >> x) {
    frame.push_back(x);
    // x — очередное число
  }

  if (!file.eof()) {
    std::cerr << "Parse error in " << argv[1] << '\n';
    return 1;
  }
  auto result = compute_stats(frame);
  if (result == std::nullopt) {
    std::cerr << "Empty input\n";
    return 1;
  }
  std::cout << *result << '\n';

  return 0;
}
