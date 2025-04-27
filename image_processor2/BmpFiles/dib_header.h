#pragma once
#include "Headers.h"

static constexpr size_t DibHeaderSize = 40;
static constexpr uint16_t Bmp24Bit = 24;

#pragma pack(push, 1)
struct DibHeader {
    uint32_t biSize{0};
    int32_t biWidth{0};
    int32_t biHeight{0};
    uint16_t biPlanes{1};
    uint16_t biBitCount{0};
    uint32_t biCompression{0};
    uint32_t biSizeImage{0};
    int32_t biXPelsPerMeter{0};
    int32_t biYPelsPerMeter{0};
    uint32_t biClrUsed{0};
    uint32_t biClrImportant{0};

    void Read(std::istream &in);

    void Write(std::ostream &out) const;
};
#pragma pack(pop)
