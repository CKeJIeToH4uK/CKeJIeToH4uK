#include "Headers.h"
#include "MakeFilters.h"
#include "image.h"

int main(const int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: ./program <input.bmp> <output.bmp> [filters...]\n";
        return 1;
    }

    const std::string input_path = argv[1];
    const std::string output_path = argv[2];
    try {
        Image image;
        image.ReadData(input_path);

        MakeFilters parser;
        parser.ParseArgs(argc, argv, image);
        parser.UseFilters(image);

        image.WriteData(output_path);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
