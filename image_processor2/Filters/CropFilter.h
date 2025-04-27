#pragma once
#include "MainFilter.h"

class CropFilter : public MainFilter {
public:
    CropFilter(size_t width, size_t height);

    void UsingFilter(Image& image) override;

private:
    size_t crop_width_;
    size_t crop_height_;
};