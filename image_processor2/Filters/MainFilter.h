#pragma once
#include "Headers.h"
#include "image.h"

class WrongParametersException final : public std::runtime_error {
public:
    explicit WrongParametersException(const std::string &msg) : std::runtime_error(msg) {
    }
};

class MainFilter {
public:
    MainFilter() = default;

    virtual void UsingFilter(Image &image) = 0;

    virtual ~MainFilter() = default;

protected:
    static void FilterForImage(const std::function<Color(size_t, size_t, Image &)> &do_filter, Image &image);
};