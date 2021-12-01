/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <ng_imploder/bin2hex/ConvertFile.hpp>
#include <iostream>
#include <fstream>
#include <extras/filesystem/paths.hpp>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ConvertFileInterface: hexToBin", "[ConvertInterface]") {

    Mock<imploder::ConvertFileInterface> mock;
    When(Method(mock, hexToBin))
        .AlwaysDo(
            [](const imploder::HexFile& hexFile) {
                imploder::BinFile binFile;
                imploder::ConvertLine converter;
                for (auto hexLine : hexFile) {
                    imploder::BinLine binline = converter.hexToBin(hexLine);
                    binFile.push_back(binline);
                }
                return binFile;
            });
    When(Method(mock, binToHex))
        .AlwaysDo(
            [](const imploder::BinFile& binFile) {
                imploder::HexFile hexFile;
                imploder::ConvertLine converter;
                for (auto binLine : binFile) {
                    imploder::HexLine hexline = converter.binToHex(binLine);
                    hexFile.push_back(hexline);
                }
                return hexFile;
            });

    imploder::HexFile hexFile;
    imploder::BinFile binFile;

    std::string h1 = ~extras::Paths("data/send.txt");

    std::ifstream in(h1);
    REQUIRE(in.good());
    while (in.good()) {
        std::string line;
        getline(in, line);
        if (in.good())
            hexFile.push_back(line);
    }

    imploder::ConvertFileInterface& i = mock.get();
    binFile = i.hexToBin(hexFile);
    hexFile = i.binToHex(binFile);
    REQUIRE(i.hexToBin(hexFile) == binFile);
    REQUIRE(i.binToHex(binFile) == hexFile);
    Verify(Method(mock, hexToBin));
    Verify(Method(mock, binToHex));
}

SCENARIO("Mock ConvertFileInterface: loadBin", "[ConvertInterface]") {

    Mock<imploder::ConvertFileInterface> mock;
    When(Method(mock, loadBin))
        .AlwaysDo(
            [](std::istream& in, int columns) {
                imploder::BinFile binFile;
                imploder::ConvertLine converter;
                while (in.good()) {
                    imploder::BinLine line;
                    for (int i = 0; i < columns && in.good();i++) {
                        byte b = 0;
                        in >> std::noskipws >> b;
                        if (in.good())
                            line.push_back(b);
                    }
                    binFile.push_back(line);
                }
                return binFile;
            });
    When(Method(mock, saveBin))
        .AlwaysDo(
            [](std::ostream& out, const imploder::BinFile& binFile) {
                for (auto binLine : binFile) {
                    for (auto b : binLine)
                        out << std::skipws << b;
                }
            });

    When(Method(mock, loadHex))
        .AlwaysDo(
            [](std::istream& in) {
                imploder::HexFile hexFile;
                imploder::ConvertLine converter;
                while (in.good()) {
                    imploder::HexLine line;
                    getline(in, line);
                    hexFile.push_back(line);
                }
                return hexFile;
            });
    When(Method(mock, saveHex))
        .AlwaysDo(
            [](std::ostream& out, const imploder::HexFile& hexFile) {
                for (auto hexLine : hexFile) {
                    out << hexLine << std::endl;
                }
            });

    imploder::BinFile binFile;
    imploder::HexFile hexFile;

    std::string b1 = ~extras::Paths("build/run-unittests-ng_imploder");
    auto b2 = "/tmp/run-unittests-ng_imploder";
    std::string h1 = ~extras::Paths("data/send.txt");
    auto h2 = "/tmp/send.txt";

    std::ifstream inBin(b1);
    REQUIRE(inBin.good());
    std::ifstream inHex(h1);
    REQUIRE(inHex.good());

    imploder::ConvertFileInterface& i = mock.get();
    binFile = i.loadBin(inBin, 40);
    hexFile = i.loadHex(inHex);
    {
        std::ofstream outBin(b2);
        REQUIRE(outBin.good());
        i.saveBin(outBin, binFile);
        std::ofstream outHex(h2);
        REQUIRE(outHex.good());
        i.saveHex(outHex, hexFile);
    }
    REQUIRE(fs::file_size(b1) == fs::file_size(b2));
    REQUIRE(fs::file_size(h1) + 1 == fs::file_size(h2));
    Verify(Method(mock, loadBin));
    Verify(Method(mock, loadHex));

}
