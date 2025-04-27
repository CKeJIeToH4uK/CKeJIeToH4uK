#define CATCH_CONFIG_MAIN

#include "../../../contrib/catch/catch.hpp"
#include "image.h"
#include "MakeFilters.h"

constexpr double EPS = 0.01;
constexpr int Args1 = 9;
constexpr int Args2 = 15;

TEST_CASE("ParallelogramTileFilter works correctly on lenna image once") {
    MakeFilters filter;
    Image image1;

    std::string input_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/lenna.bmp";
    std::string output_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/"
        "lenna_test_parallel.bmp";

    std::string program_name = "Program";
    std::string filter_flag = "-parallelogram";
    std::string angle = "45";
    std::string acute_angle = "45";
    std::string width = "1500";
    std::string center_x = "256";
    std::string center_y = "120";

    char *argv[] = {&program_name[0], &input_path[0], &output_path[0], &filter_flag[0], &angle[0],
                    &acute_angle[0],  &width[0],      &center_x[0],    &center_y[0]};

    filter.ParseArgs(Args1, argv, image1);
    image1.ReadData(input_path);
    filter.UseFilters(image1);
    image1.WriteData(output_path);

    Image expected;
    expected.ReadData(
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/"
        "lenna_test_parallel.bmp");

    REQUIRE(image1.GetHeight() == expected.GetHeight());
    REQUIRE(image1.GetWidth() == expected.GetWidth());

    for (size_t i = 0; i < image1.GetHeight(); ++i) {
        for (size_t j = 0; j < image1.GetWidth(); ++j) {
            size_t idx = i * image1.GetWidth() + j;
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetRed() - expected.GetPixelData()[idx].GetRed()) < EPS);
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetGreen() - expected.GetPixelData()[idx].GetGreen()) < EPS);
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetBlue() - expected.GetPixelData()[idx].GetBlue()) < EPS);
        }
    }
}

TEST_CASE("ParallelogramTileFilter works correctly with two consecutive filters") {
    MakeFilters filter;
    Image image1;

    std::string input_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/lenna.bmp";
    std::string output_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/"
        "lenna_test_parallel_parallel.bmp";

    std::string program_name = "Program";
    std::string filter_flag1 = "-parallelogram";
    std::string angle1 = "45";
    std::string acute_angle1 = "45";
    std::string width1 = "1500";
    std::string center_x1 = "256";
    std::string center_y1 = "120";

    std::string filter_flag2 = "-parallelogram";
    std::string angle2 = "45";
    std::string acute_angle2 = "45";
    std::string width2 = "1000";
    std::string center_x2 = "256";
    std::string center_y2 = "256";

    char *argv[] = {&program_name[0], &input_path[0],   &output_path[0], &filter_flag1[0], &angle1[0],
                    &acute_angle1[0], &width1[0],       &center_x1[0],   &center_y1[0],    &filter_flag2[0],
                    &angle2[0],       &acute_angle2[0], &width2[0],      &center_x2[0],    &center_y2[0]};

    filter.ParseArgs(Args2, argv, image1);
    image1.ReadData(input_path);
    filter.UseFilters(image1);
    image1.WriteData(output_path);

    Image expected;
    expected.ReadData(
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/"
        "lenna_test_parallel_parallel.bmp");

    REQUIRE(image1.GetHeight() == expected.GetHeight());
    REQUIRE(image1.GetWidth() == expected.GetWidth());

    for (size_t i = 0; i < image1.GetHeight(); ++i) {
        for (size_t j = 0; j < image1.GetWidth(); ++j) {
            size_t idx = i * image1.GetWidth() + j;
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetRed() - expected.GetPixelData()[idx].GetRed()) < EPS);
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetGreen() - expected.GetPixelData()[idx].GetGreen()) < EPS);
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetBlue() - expected.GetPixelData()[idx].GetBlue()) < EPS);
        }
    }
}
TEST_CASE("ParallelogramTileFilter throws exception on invalid parameters") {
    std::string program_name = "Program";
    std::string input_file = "fake_input.bmp";
    std::string output_file = "fake_output.bmp";
    std::string filter_flag = "-parallelogram";
    std::string angle = "45";

    char *argv[] = {&program_name[0], &input_file[0], &output_file[0], &filter_flag[0], &angle[0]};

    int argc = sizeof(argv) / sizeof(char *);

    try {
        Image image;
        MakeFilters filter;
        filter.ParseArgs(argc, argv, image);
    } catch (const std::exception &e) {
        REQUIRE(std::string(e.what()).find("Usage") != std::string::npos);
        return;
    }

    FAIL("Expected exception due to missing parameters");
}

TEST_CASE("Unknown filter throws exception") {

    std::string program_name = "Program";
    std::string input_file = "input.bmp";
    std::string output_file = "output.bmp";
    std::string unknown_flag = "-unknownfilter";

    char *argv[] = {&program_name[0], &input_file[0], &output_file[0], &unknown_flag[0]};

    try {
        Image image;
        MakeFilters filter;
        filter.ParseArgs(4, argv, image);
    } catch (const std::exception &e) {
        REQUIRE(std::string(e.what()).find("Unknown filter") != std::string::npos);
        return;
    }

    FAIL("Expected exception due to unknown filter");
}

TEST_CASE("Image is preserved after WriteData and ReadData") {
    MakeFilters filter;
    Image image1;

    std::string input_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/lenna.bmp";
    std::string temp_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/lenna_saved.bmp";

    std::string program_name = "Program";
    std::string filter_flag = "-parallelogram";
    std::string angle = "45";
    std::string acute_angle = "45";
    std::string width = "1500";
    std::string center_x = "256";
    std::string center_y = "120";

    char *argv[] = {&program_name[0], &input_path[0], &temp_path[0], &filter_flag[0], &angle[0],
                    &acute_angle[0],  &width[0],      &center_x[0],  &center_y[0]};

    filter.ParseArgs(Args1, argv, image1);
    image1.ReadData(input_path);
    filter.UseFilters(image1);
    image1.WriteData(temp_path);

    Image reread;
    reread.ReadData(temp_path);

    REQUIRE(reread.GetHeight() == image1.GetHeight());
    REQUIRE(reread.GetWidth() == image1.GetWidth());

    for (size_t i = 0; i < image1.GetHeight(); ++i) {
        for (size_t j = 0; j < image1.GetWidth(); ++j) {
            size_t idx = i * image1.GetWidth() + j;
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetRed() - reread.GetPixelData()[idx].GetRed()) < EPS);
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetGreen() - reread.GetPixelData()[idx].GetGreen()) < EPS);
            REQUIRE(std::abs(image1.GetPixelData()[idx].GetBlue() - reread.GetPixelData()[idx].GetBlue()) < EPS);
        }
    }
}

TEST_CASE("ReadData throws exception on non-existent file") {
    try {
        Image image;
        image.ReadData("/path/that/does/not/exist.bmp");
    } catch (const std::exception &e) {
        REQUIRE(std::string(e.what()).find("Cannot open file") == std::string::npos);
        return;
    }
    FAIL("Expected exception on nonexistent file");
}

TEST_CASE("ParseArgs throws on wrong filter parameter") {
    MakeFilters filters;
    Image image;

    std::string program = "Program";
    std::string input = "input.bmp";
    std::string output = "output.bmp";
    std::string blur = "-blur";
    std::string wrong_param = "lol";

    char *argv[] = {&program[0], &input[0], &output[0], &blur[0], &wrong_param[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image), Catch::Contains("Usage: -blur"));
}

TEST_CASE("ParseArgs throws on wrong input filename extension") {
    MakeFilters filters;
    Image image;

    std::string program = "Program";
    std::string input = "wrong.txt";
    std::string output = "output.bmp";
    std::string blur = "-blur";
    std::string sigma = "1.0";

    char *argv[] = {&program[0], &input[0], &output[0], &blur[0], &sigma[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image), Catch::Contains(".bmp"));
}

TEST_CASE("MakeFilters::ParseArgs sets paths so Image::ReadData works") {
    MakeFilters filters;
    Image image;

    std::string program = "Program";
    std::string input_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/lenna_saved.bmp";
    std::string output_path =
        "/Users/bulat/ami-Bulat-Mannanov-CKeJIeToH4uK/tasks/image_processor/TestBmpParallelogramm/test_out.bmp";
    std::string filter_flag = "-sharp";

    char *argv[] = {&program[0], &input_path[0], &output_path[0], &filter_flag[0]};

    REQUIRE_NOTHROW(filters.ParseArgs(4, argv, image));
    REQUIRE_NOTHROW(image.ReadData(input_path));
    REQUIRE(image.GetWidth() > 0);
    REQUIRE(image.GetHeight() > 0);
}

TEST_CASE("Image::CalculatePadding works correctly") {
    REQUIRE(Image::CalculatePadding(1) == 1);
    REQUIRE(Image::CalculatePadding(2) == 2);
    REQUIRE(Image::CalculatePadding(3) == 3);
    REQUIRE(Image::CalculatePadding(4) == 0);
    REQUIRE(Image::CalculatePadding(5) == 1);
    REQUIRE(Image::CalculatePadding(6) == 2);
    REQUIRE(Image::CalculatePadding(7) == 3);
    REQUIRE(Image::CalculatePadding(8) == 0);
}

TEST_CASE("Image::SetSize changes dimensions and resizes pixel array") {
    constexpr int InitialWidth = 10;
    constexpr int InitialHeight = 20;
    constexpr size_t InitialPixels = InitialWidth * InitialHeight;

    Image img(InitialWidth, InitialHeight);
    REQUIRE(img.GetWidth() == InitialWidth);
    REQUIRE(img.GetHeight() == InitialHeight);
    REQUIRE(img.GetPixelData().size() == InitialPixels);

    constexpr int FirstResizeWidth = 5;
    constexpr int FirstResizeHeight = 5;
    constexpr size_t FirstResizePixels = FirstResizeWidth * FirstResizeHeight;

    img.SetSize(FirstResizeWidth, FirstResizeHeight);
    REQUIRE(img.GetWidth() == FirstResizeWidth);
    REQUIRE(img.GetHeight() == FirstResizeHeight);
    REQUIRE(img.GetPixelData().size() == FirstResizePixels);

    constexpr int SecondResizeWidth = 8;
    constexpr int SecondResizeHeight = 8;
    constexpr size_t SecondResizePixels = SecondResizeWidth * SecondResizeHeight;

    img.SetSize(SecondResizeWidth, SecondResizeHeight);
    REQUIRE(img.GetWidth() == SecondResizeWidth);
    REQUIRE(img.GetHeight() == SecondResizeHeight);
    REQUIRE(img.GetPixelData().size() == SecondResizePixels);
}

TEST_CASE("ParseArgs -crop with negative parameters throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string crop_flag = "-crop";
    std::string w = "-5";
    std::string h = "10";

    char *argv[] = {&prog[0], &in[0], &out[0], &crop_flag[0], &w[0], &h[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(6, argv, image), Catch::Contains("Usage: -crop <width> <height>"));
}

TEST_CASE("ParseArgs -blur missing sigma throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string blur = "-blur";

    char *argv[] = {&prog[0], &in[0], &out[0], &blur[0]};
    REQUIRE_THROWS_WITH(filters.ParseArgs(4, argv, image), Catch::Contains("Usage: -blur <sigma>"));
}

TEST_CASE("ParseArgs -blur with non-numeric sigma throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string blur = "-blur";
    std::string sigma = "abc";

    char *argv[] = {&prog[0], &in[0], &out[0], &blur[0], &sigma[0]};
    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image), Catch::Contains("Usage: -blur <sigma>"));
}

TEST_CASE("ParseArgs -edge missing threshold throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string edge = "-edge";

    char *argv[] = {&prog[0], &in[0], &out[0], &edge[0]};
    REQUIRE_THROWS_WITH(filters.ParseArgs(4, argv, image), Catch::Contains("Edge filter requires 1 parameter"));
}

TEST_CASE("ParseArgs -parallelogram with missing parameters throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string flag = "-parallelogram";
    std::string angle = "30";

    char *argv[] = {&prog[0], &in[0], &out[0], &flag[0], &angle[0]};
    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image),
                        Catch::Contains("Usage: -parallelogram <angle> <acuteAngle> <width> <centerX> <centerY>"));
}

TEST_CASE("ParseArgs -parallelogram with non-numeric parameter throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string flag = "-parallelogram";
    std::string a1 = "30";
    std::string a2 = "45";
    std::string w = "500";
    std::string cx = "invalid";
    std::string cy = "300";

    char *argv[] = {&prog[0], &in[0], &out[0], &flag[0], &a1[0], &a2[0], &w[0], &cx[0], &cy[0]};
    REQUIRE_THROWS_WITH(filters.ParseArgs(9, argv, image),
                        Catch::Contains("Usage: -parallelogram <angle> <acuteAngle> <width> <centerX> <centerY>"));
}

TEST_CASE("ParseArgs -sharp with extra parameter throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string sharp = "-sharp";
    std::string extra = "123";

    char *argv[] = {&prog[0], &in[0], &out[0], &sharp[0], &extra[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image), Catch::Contains("Unknown filter"));
}

TEST_CASE("ParseArgs -edge without parameter throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string edge = "-edge";

    char *argv[] = {&prog[0], &in[0], &out[0], &edge[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(4, argv, image), Catch::Contains("Edge filter requires 1 parameter"));
}

TEST_CASE("ParseArgs -edge with non-numeric threshold throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string edge = "-edge";
    std::string bad = "abc";

    char *argv[] = {&prog[0], &in[0], &out[0], &edge[0], &bad[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image),
                        Catch::Contains("Usage: -edge <threshold> (threshold must be number)"));
}

TEST_CASE("ParseArgs -neg with extra parameter throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string neg = "-neg";
    std::string extra = "oops";

    char *argv[] = {&prog[0], &in[0], &out[0], &neg[0], &extra[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image), Catch::Contains("Unknown filter"));
}

TEST_CASE("ParseArgs -gs with extra parameter throws") {
    MakeFilters filters;
    Image image;

    std::string prog = "prog";
    std::string in = "input.bmp";
    std::string out = "out.bmp";
    std::string gs = "-gs";
    std::string junk = "123";

    char *argv[] = {&prog[0], &in[0], &out[0], &gs[0], &junk[0]};

    REQUIRE_THROWS_WITH(filters.ParseArgs(5, argv, image), Catch::Contains("Unknown filter"));
}