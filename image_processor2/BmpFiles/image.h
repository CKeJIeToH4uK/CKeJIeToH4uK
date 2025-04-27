#pragma once
#include "Headers.h"
#include "bmp_header.h"
#include "dib_header.h"
#include "color.h"

constexpr int BytesPerPixel = 3;
constexpr int BmpPaddingAlign = 4;
constexpr float MaxColorValue = 255.0f;

class Image {
private:
    BmpHeader file_header_;
    DibHeader dib_header_;

    size_t width_ = 0;
    size_t height_ = 0;

    std::vector<Color> pixel_data_;

public:
    Image() = default;

    Image(size_t width, size_t height);

    void ReadData(const std::string &path);

    void WriteData(const std::string &path) const;

    [[nodiscard]] size_t GetWidth() const {
        return width_;
    }
    [[nodiscard]] size_t GetHeight() const {
        return height_;
    }

    [[nodiscard]] const std::vector<Color> &GetPixelData() const {
        return pixel_data_;
    }

    Color &Pixel(size_t x, size_t y);

    [[nodiscard]] const Color &Pixel(size_t x, size_t y) const;

    static unsigned char ClampColor(float value);

    void SetSize(size_t new_width, size_t new_height);

    void SetPixelData(std::vector<Color> new_data);

    [[nodiscard]] static size_t CalculatePadding(size_t width);
};