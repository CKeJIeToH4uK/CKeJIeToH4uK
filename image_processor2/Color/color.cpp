#include "color.h"
#include <iostream>

Color::Color() : red_(0), green_(0), blue_(0) {
}

Color::Color(float input_red, float input_green, float input_blue)
    : red_(input_red), green_(input_green), blue_(input_blue) {
}

void Color::Print() const {
    std::cout << red_ << " " << green_ << " " << blue_ << std::endl;
}

bool Color::operator==(const Color &color) const {
    return (this->red_ == color.red_) && (this->green_ == color.green_) && (this->blue_ == color.blue_);
}

float Color::GetRed() const {
    return red_;
}

float Color::GetGreen() const {
    return green_;
}

float Color::GetBlue() const {
    return blue_;
}