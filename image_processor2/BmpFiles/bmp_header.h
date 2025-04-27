#pragma once
#include "Headers.h"

static constexpr size_t BmpHeaderSize = 14;
static constexpr uint16_t BmpSignature = 0x4D42;

#pragma pack(push, 1)
struct BmpHeader {
    uint16_t bfType{0};
    uint32_t bfSize{0};
    uint16_t bfReserved1{0};
    uint16_t bfReserved2{0};
    uint32_t bfOffBits{0};

    void Read(std::istream &in);

    void Write(std::ostream &out) const;
};
#pragma pack(pop)