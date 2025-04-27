#pragma once
#include "FormulaFilter.h"

constexpr float RedWeight = 0.299f;
constexpr float GreenWeight = 0.587f;
constexpr float BlueWeight = 0.114f;

class GrayscaleFilter : public FormulaFilter {
public:
    GrayscaleFilter() = default;

protected:
    Color Compute(size_t x, size_t y, const Color &color) const override;
};
