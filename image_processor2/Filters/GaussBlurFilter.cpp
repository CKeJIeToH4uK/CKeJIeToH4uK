#include "GaussBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter(float sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::GenerateKernel1D(float sigma, std::vector<float>& kernel_out, int& radius_out) {
    radius_out = static_cast<int>(std::ceil(GaussianRadiusScale * sigma));
    kernel_out.resize(2 * radius_out + 1);

    float sum = 0.0f;
    for (int i = -radius_out; i <= radius_out; ++i) {
        float fi = static_cast<float>(i);
        float weight = std::exp(-(fi * fi) / (GaussianDenomFactor * sigma * sigma));
        kernel_out[i + radius_out] = weight;
        sum += weight;
    }

    for (float& value : kernel_out) {
        value /= sum;
    }
}

void GaussianBlurFilter::UsingFilter(Image& image) {
    std::vector<float> kernel;
    int radius = 0;
    GenerateKernel1D(sigma_, kernel, radius);

    size_t width = image.GetWidth();
    size_t height = image.GetHeight();
    std::vector<Color> temp(width * height);
    std::vector<Color> result(width * height);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int k = -radius; k <= radius; ++k) {
                int nx = std::clamp<int>(static_cast<int>(x) + k, 0, static_cast<int>(width) - 1);
                float weight = kernel[k + radius];
                const Color& c = image.Pixel(nx, y);
                r += c.GetRed() * weight;
                g += c.GetGreen() * weight;
                b += c.GetBlue() * weight;
            }
            temp[y * width + x] = Color(r, g, b);
        }
    }

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int k = -radius; k <= radius; ++k) {
                int ny = std::clamp<int>(static_cast<int>(y) + k, 0, static_cast<int>(height) - 1);
                float weight = kernel[k + radius];
                const Color& c = temp[ny * width + x];
                r += c.GetRed() * weight;
                g += c.GetGreen() * weight;
                b += c.GetBlue() * weight;
            }
            result[y * width + x] = Color(r, g, b);
        }
    }

    image.SetPixelData(std::move(result));
}
