#pragma once
#include "MainFilter.h"

class FormulaFilter : public MainFilter {
public:
    FormulaFilter() = default;

    void UsingFilter(Image& image) override;

protected:
    virtual Color Compute(size_t x, size_t y, const Color& color) const = 0;
};