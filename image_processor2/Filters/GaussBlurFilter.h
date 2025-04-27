#pragma once
#include "Headers.h"
#include "MainFilter.h"

constexpr float GaussianRadiusScale = 3.0f;
constexpr float GaussianDenomFactor = 2.0f;

class GaussianBlurFilter : public MainFilter {
public:
    explicit GaussianBlurFilter(float sigma);

    void UsingFilter(Image& image) override;

private:
    float sigma_;

    static void GenerateKernel1D(float sigma, std::vector<float>& kernel_out, int& radius_out);
};