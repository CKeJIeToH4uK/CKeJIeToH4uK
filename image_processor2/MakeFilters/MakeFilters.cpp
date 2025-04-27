#include "MakeFilters.h"
#include "CropFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussBlurFilter.h"
#include "GrayscaleFilter.h"
#include "NegativeFilter.h"
#include "SharpFilter.h"
#include "ParallelolgrammFilter.h"

static bool EndsWithBMP(const std::string &path) {
    if (path.size() < 4) {
        return false;
    }
    return path.compare(path.size() - 4, 4, ".bmp") == 0;
}

void MakeFilters::ParseArgs(int argc, char **argv, Image &image) {
    if (argc < 3) {
        std::cout << "Usage: ./program <input.bmp> <output.bmp> [filters...]\n";
        std::cout << "Available filters:\n";
        std::cout << "  -neg               Negative\n";
        std::cout << "  -sharp             Sharpening\n";
        std::cout << "  -crop <w> <h>      Crop to width x height\n";
        std::cout << "  -gs                Grayscale\n";
        std::cout << "  -blur <sigma>      Gaussian blur\n";
        std::cout << "  -edge <threshold>  Edge detection\n";
        std::cout << "  -parallelogram <angle> <acuteAngle> <width> <centerX> <centerY>\n";
        throw WrongInputException("Not enough arguments");
    }

    if (!EndsWithBMP(argv[1])) {
        throw WrongInputException("Input file must be a .bmp");
    }

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-neg") {
            filters_.push_back(std::make_unique<NegativeFilter>());
        } else if (arg == "-parallelogram") {

            if (i + MagicFive >= argc) {
                throw WrongInputException("Usage: -parallelogram <angle> <acuteAngle> <width> <centerX> <centerY>");
            }
            try {
                float angle = std::stof(argv[++i]);
                float acute_angle = std::stof(argv[++i]);
                float width = std::stof(argv[++i]);
                size_t cx = static_cast<size_t>(std::stoi(argv[++i]));
                size_t cy = static_cast<size_t>(std::stoi(argv[++i]));
                filters_.push_back(std::make_unique<ParallelogramTileFilter>(angle, acute_angle, width, cx, cy));
            } catch (const std::exception &) {
                throw WrongInputException(
                    "Usage: -parallelogram <angle> <acuteAngle> <width> <centerX> <centerY> (all must be numbers)");
            }
        }

        else if (arg == "-sharp") {
            filters_.push_back(std::make_unique<SharpeningFilter>());
        }

        else if (arg == "-gs") {
            filters_.push_back(std::make_unique<GrayscaleFilter>());
        } else if (arg == "-crop") {
            if (i + 2 >= argc) {
                throw WrongInputException("Usage: -crop <width> <height>");
            }

            int width = std::stoi(argv[i + 1]);
            int height = std::stoi(argv[i + 2]);

            if (width <= 0 || height <= 0) {
                throw WrongInputException("Usage: -crop <width> <height>");
            }

            filters_.push_back(std::make_unique<CropFilter>(width, height));
            i += 2;
        }

        else if (arg == "-edge") {
            if (i + 1 >= argc) {
                throw WrongInputException("Edge filter requires 1 parameter: threshold");
            }
            try {
                float threshold = std::stof(argv[++i]);
                filters_.push_back(std::make_unique<EdgeDetectionFilter>(threshold));
            } catch (...) {
                throw WrongInputException("Usage: -edge <threshold> (threshold must be number)");
            }
        }

        else if (arg == "-blur") {
            if (i + 1 >= argc) {
                throw WrongInputException("Usage: -blur <sigma>");
            }
            try {
                float sigma = std::stof(argv[++i]);
                filters_.push_back(std::make_unique<GaussianBlurFilter>(sigma));
            } catch (...) {
                throw WrongInputException("Usage: -blur <sigma> (sigma must be number)");
            }
        }

        else {
            throw WrongInputException("Unknown filter: " + arg);
        }
    }
}

void MakeFilters::UseFilters(Image &image) const {
    for (auto &filter : filters_) {
        filter->UsingFilter(image);
    }
}
