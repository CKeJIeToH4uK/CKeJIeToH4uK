#include "FormulaFilter.h"

void FormulaFilter::UsingFilter(Image& image) {
    std::function<Color(size_t, size_t, Image&)> filter = [this](size_t x, size_t y, Image& img) {
        const Color& input = img.Pixel(x, y);
        return this->Compute(x, y, input);
    };

    FilterForImage(filter, image);
}