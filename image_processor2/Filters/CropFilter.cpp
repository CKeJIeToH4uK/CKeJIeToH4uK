#include "CropFilter.h"

CropFilter::CropFilter(size_t width, size_t height) : crop_width_(width), crop_height_(height) {
}

void CropFilter::UsingFilter(Image& image) {
    size_t new_width = std::min(crop_width_, image.GetWidth());
    size_t new_height = std::min(crop_height_, image.GetHeight());

    std::vector<Color> cropped;
    cropped.reserve(new_width * new_height);

    size_t y_start = image.GetHeight() - new_height;
    for (size_t y = y_start; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < new_width; ++x) {
            cropped.push_back(image.Pixel(x, y));
        }
    }

    image.SetPixelData(std::move(cropped));
    image.SetSize(new_width, new_height);
}