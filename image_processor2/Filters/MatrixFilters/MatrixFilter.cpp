#include "MatrixFilter.h"

MatrixFilter::MatrixFilter(const std::vector<std::vector<float> > &kernel) : kernel_(kernel) {
    if (kernel.size() != 3 || kernel[0].size() != 3 || kernel[1].size() != 3 || kernel[2].size() != 3) {
        throw WrongParametersException("Kernel must be 3x3");
    }
}

void MatrixFilter::UsingFilter(Image &image) {
    std::function<Color(size_t, size_t, Image &)> filter = [this](size_t x, size_t y, Image &img) {
        return ApplyKernel(x, y, img, kernel_);
    };

    FilterForImage(filter, image);
}

Color MatrixFilter::ApplyKernel(size_t x, size_t y, Image &image, const std::vector<std::vector<float> > &kernel) {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    for (int ky = -1; ky <= 1; ++ky) {
        for (int kx = -1; kx <= 1; ++kx) {
            int nx = std::clamp(static_cast<int>(x) + kx, 0, static_cast<int>(image.GetWidth()) - 1);
            int ny = std::clamp(static_cast<int>(y) + ky, 0, static_cast<int>(image.GetHeight()) - 1);
            const Color &c = image.Pixel(nx, ny);
            float k = kernel[ky + 1][kx + 1];
            r += c.GetRed() * k;
            g += c.GetGreen() * k;
            b += c.GetBlue() * k;
        }
    }

    return Color{std::clamp(r, 0.0f, 1.0f), std::clamp(g, 0.0f, 1.0f), std::clamp(b, 0.0f, 1.0f)};
}
