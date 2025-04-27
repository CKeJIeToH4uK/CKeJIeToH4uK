#include "bmp_header.h"

void BmpHeader::Read(std::istream &in) {
    in.read(reinterpret_cast<char *>(this), sizeof(BmpHeader));

    if (bfType != BmpSignature) {
        throw std::runtime_error("Not a BMP file (invalid signature).");
    }
}

void BmpHeader::Write(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(this), sizeof(BmpHeader));
}
