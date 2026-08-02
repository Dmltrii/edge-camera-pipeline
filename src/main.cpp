#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::string input_path = argv[1];
    std::cout << "Processing input: " << input_path << "\n";

    return 0;
}
