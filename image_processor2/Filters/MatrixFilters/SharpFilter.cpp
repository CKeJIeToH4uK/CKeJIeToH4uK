#include "SharpFilter.h"

SharpeningFilter::SharpeningFilter() : MatrixFilter({{0, -1, 0}, {-1, MagicFive, -1}, {0, -1, 0}}) {
}
