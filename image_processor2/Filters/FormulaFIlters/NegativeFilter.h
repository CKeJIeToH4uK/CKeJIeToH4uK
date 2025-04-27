#pragma once
#include "FormulaFilter.h"

class NegativeFilter : public FormulaFilter {
public:
    NegativeFilter() = default;

protected:
    [[nodiscard]] Color Compute(size_t x, size_t y, const Color& color) const override;
};