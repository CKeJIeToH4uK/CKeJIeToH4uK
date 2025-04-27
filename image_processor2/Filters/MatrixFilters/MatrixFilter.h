#pragma once
#include "Headers.h"
#include "MainFilter.h"

class MatrixFilter : public MainFilter {
public:
    explicit MatrixFilter(const std::vector<std::vector<float>> &kernel = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}});

    void UsingFilter(Image &image) override;

protected:
    std::vector<std::vector<float>> kernel_;

    static Color ApplyKernel(size_t x, size_t y, Image &image, const std::vector<std::vector<float>> &kernel);
};