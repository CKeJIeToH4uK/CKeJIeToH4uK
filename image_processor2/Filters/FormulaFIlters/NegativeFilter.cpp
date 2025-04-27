#include "NegativeFilter.h"

Color NegativeFilter::Compute(size_t, size_t, const Color &color) const {
    return {1.0f - color.GetRed(), 1.0f - color.GetGreen(), 1.0f - color.GetBlue()};
}
