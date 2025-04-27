#include "MainFilter.h"

void MainFilter::FilterForImage(const std::function<Color(size_t, size_t, Image &)> &do_filter, Image &image) {
    std::vector<Color> new_data(image.GetWidth() * image.GetHeight());

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            new_data[y * image.GetWidth() + x] = do_filter(x, y, image);
        }
    }

    image.SetPixelData(std::move(new_data));
}