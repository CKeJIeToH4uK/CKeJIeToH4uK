#pragma once
#include "MainFilter.h"

static constexpr float PiF = 3.1415926f;
static constexpr float DoublePeriod = 2.0f;

class ParallelogramTileFilter : public MainFilter {
public:
    ParallelogramTileFilter(float angle, float acute_angle, float width, size_t center_x, size_t center_y);

    void UsingFilter(Image& image) override;

private:
    float angle_;
    float acute_angle_;
    float width_;
    size_t center_x_;
    size_t center_y_;

    static float ReflectCoord(float coord, float period);

    void MapToSource(float& x, float& y) const;
};