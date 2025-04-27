#include "ParallelolgrammFilter.h"

ParallelogramTileFilter::ParallelogramTileFilter(float angle, float acute_angle, float width, size_t center_x,
                                                 size_t center_y)
    : angle_(angle), acute_angle_(acute_angle), width_(width), center_x_(center_x), center_y_(center_y) {
}

float ParallelogramTileFilter::ReflectCoord(float coord, float period) {

    float double_p = DoublePeriod * period;

    coord = std::fmod(coord, double_p);
    if (coord < 0) {
        coord += double_p;
    }

    if (coord > period) {
        coord = double_p - coord;
    }
    return coord;
}

void ParallelogramTileFilter::MapToSource(float &x, float &y) const {

    x -= static_cast<float>(center_x_);
    y -= static_cast<float>(center_y_);

    float tx = x + std::tan(angle_) * y;
    float ty = y + std::tan(acute_angle_) * x;

    x = tx;
    y = ty;
}

void ParallelogramTileFilter::UsingFilter(Image &image) {
    std::vector<Color> new_data(image.GetWidth() * image.GetHeight());
    size_t w = image.GetWidth();
    size_t h = image.GetHeight();

    for (size_t row = 0; row < h; ++row) {
        for (size_t col = 0; col < w; ++col) {
            float fx = static_cast<float>(col);
            float fy = static_cast<float>(row);

            MapToSource(fx, fy);

            float tx = ReflectCoord(fx, width_);
            float ty = ReflectCoord(fy, width_);

            int sx = static_cast<int>(std::round(tx));
            int sy = static_cast<int>(std::round(ty));

            sx = std::clamp(sx, 0, static_cast<int>(w) - 1);
            sy = std::clamp(sy, 0, static_cast<int>(h) - 1);

            new_data[row * w + col] = image.Pixel(sx, sy);
        }
    }
    image.SetPixelData(std::move(new_data));
}
