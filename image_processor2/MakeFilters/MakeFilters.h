#pragma once

#include "Headers.h"
#include "MainFilter.h"
#include "image.h"

static constexpr int FiveArgs = 5;

class MakeFilters {
public:
    class WrongInputException final : public std::runtime_error {
    public:
        explicit WrongInputException(const std::string &msg) : std::runtime_error(msg) {
        }
    };

    void ParseArgs(int argc, char **argv, Image &image);

    void UseFilters(Image &image) const;

private:
    std::vector<std::unique_ptr<MainFilter> > filters_;
};