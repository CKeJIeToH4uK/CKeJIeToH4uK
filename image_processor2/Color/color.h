#pragma once

class Color {
public:
    Color();

    Color(float input_red, float input_green, float input_blue);

    void Print() const;

    bool operator==(const Color &color) const;

    [[nodiscard]] float GetRed() const;

    [[nodiscard]] float GetGreen() const;

    [[nodiscard]] float GetBlue() const;

private:
    float red_;
    float green_;
    float blue_;
};
