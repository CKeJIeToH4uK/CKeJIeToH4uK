#pragma once
#include "MatrixFilter.h"
#include "GrayscaleFilter.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    explicit EdgeDetectionFilter(float threshold);

    void UsingFilter(Image& image) override;

private:
    float threshold_;
};