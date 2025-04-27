#include "GrayscaleFilter.h"

Color GrayscaleFilter::Compute(size_t, size_t, const Color& color) const {
    float gray = RedWeight * color.GetRed() + GreenWeight * color.GetGreen() + BlueWeight * color.GetBlue();
    return {gray, gray, gray};
}