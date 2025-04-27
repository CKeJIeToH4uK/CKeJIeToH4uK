#include "dib_header.h"

void DibHeader::Read(std::istream &in) {
    in.read(reinterpret_cast<char *>(this), sizeof(DibHeader));

    if (biSize != DibHeaderSize) {
        throw std::runtime_error("Unsupported DIB header size.");
    }
    if (biBitCount != Bmp24Bit || biCompression != 0) {
        throw std::runtime_error("Only 24-bit uncompressed BMP supported.");
    }
}

void DibHeader::Write(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(this), sizeof(DibHeader));
}
