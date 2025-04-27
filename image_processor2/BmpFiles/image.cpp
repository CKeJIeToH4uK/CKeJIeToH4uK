#include "image.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

Image::Image(size_t width, size_t height) : width_(width), height_(height), pixel_data_(width * height) {
}

void Image::ReadData(const std::string &path) {
    std::ifstream fin(path, std::ios::binary);

    file_header_.Read(fin);
    dib_header_.Read(fin);

    width_ = dib_header_.biWidth;
    height_ = dib_header_.biHeight;

    size_t padding = CalculatePadding(width_);

    pixel_data_.resize(width_ * height_);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char bgr[3];
            fin.read(reinterpret_cast<char *>(bgr), 3);
            const Color color(static_cast<float>(bgr[2]) / MaxColorValue, static_cast<float>(bgr[1]) / MaxColorValue,
                              static_cast<float>(bgr[0]) / MaxColorValue);
            pixel_data_[y * width_ + x] = color;
        }

        fin.ignore(static_cast<std::streamsize>(padding));
    }
    fin.close();
}

void Image::WriteData(const std::string &path) const {
    std::ofstream fout(path, std::ios::binary);
    BmpHeader out_file_header = file_header_;
    DibHeader out_dib_header = dib_header_;

    out_dib_header.biWidth = static_cast<int32_t>(width_);
    out_dib_header.biHeight = static_cast<int32_t>(height_);

    size_t padding = CalculatePadding(width_);
    out_dib_header.biSizeImage = static_cast<uint32_t>((3 * width_ + padding) * height_);
    out_file_header.bfSize = BmpHeaderSize + DibHeaderSize + out_dib_header.biSizeImage;

    out_file_header.Write(fout);
    out_dib_header.Write(fout);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            Color c = pixel_data_[y * width_ + x];
            unsigned char bgr[3] = {ClampColor(c.GetBlue()), ClampColor(c.GetGreen()), ClampColor(c.GetRed())};
            fout.write(reinterpret_cast<char *>(bgr), 3);
        }
        constexpr unsigned char Pad[3] = {0, 0, 0};
        fout.write(reinterpret_cast<const char *>(Pad), static_cast<std::streamsize>(padding));
    }

    fout.close();
}

size_t Image::CalculatePadding(size_t width) {
    return (4 - (3 * width) % 4) % 4;
}

Color &Image::Pixel(size_t x, size_t row) {
    return pixel_data_[row * width_ + x];
}

const Color &Image::Pixel(const size_t x, const size_t row) const {
    return pixel_data_[row * width_ + x];
}

unsigned char Image::ClampColor(float value) {
    return static_cast<unsigned char>(std::max(0.0f, std::min(1.0f, value)) * MaxColorValue);
}

void Image::SetSize(size_t new_width, size_t new_height) {
    width_ = new_width;
    height_ = new_height;
    pixel_data_.resize(width_ * height_);
}

void Image::SetPixelData(std::vector<Color> new_data) {
    pixel_data_ = std::move(new_data);
}