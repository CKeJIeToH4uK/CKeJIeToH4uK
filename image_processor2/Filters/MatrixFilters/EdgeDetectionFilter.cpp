#include "EdgeDetectionFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(float threshold)
    : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), threshold_(threshold) {
}

void EdgeDetectionFilter::UsingFilter(Image &image) {
    GrayscaleFilter().UsingFilter(image);

    MatrixFilter::UsingFilter(image);

    std::function<Color(size_t, size_t, Image &)> threshold_fn = [this](size_t x, size_t y, Image &img) {
        float v = img.Pixel(x, y).GetRed();
        return (v > threshold_) ? Color(1.0f, 1.0f, 1.0f) : Color(0.0f, 0.0f, 0.0f);
    };

    FilterForImage(threshold_fn, image);
}
