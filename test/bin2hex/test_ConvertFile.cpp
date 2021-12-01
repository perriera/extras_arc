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
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

SCENARIO("Test ConvertFileInterface: hexToBin", "[ConvertInterface]") {

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

    imploder::ConvertFile converter;
    imploder::ConvertFileInterface& i = converter;
    binFile = i.hexToBin(hexFile);
    hexFile = i.binToHex(binFile);
    REQUIRE(i.hexToBin(hexFile) == binFile);
    REQUIRE(i.binToHex(binFile) == hexFile);

}

SCENARIO("Test ConvertFileInterface: saveHex", "[ConvertInterface]") {

    std::string b1 = ~extras::Paths("build/run-unittests-ng_imploder");
    auto b2 = "/tmp/run-unittests-ng_imploder";
    std::string h1 = ~extras::Paths("data/send.txt");
    auto h2 = "/tmp/send.txt";
    std::ifstream inBin(b1);
    REQUIRE(inBin.good());
    std::ifstream inHex(h1);
    REQUIRE(inHex.good());

    imploder::BinFile binFile;
    imploder::HexFile hexFile;

    imploder::ConvertFile converter;
    imploder::ConvertFileInterface& i = converter;
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

}

SCENARIO("Test ConvertFileInterface: saveHex2", "[ConvertInterface]") {

    auto f1 = "build/run-unittests-ng_imploder";
    auto f2 = "/tmp/run-unittests-ng_imploder.txt";
    auto f3 = "/tmp/run-unittests-ng_imploder";

    std::ifstream inBin(f1);
    REQUIRE(inBin.good());
    imploder::BinFile binFile;
    imploder::ConvertFile converter;
    binFile = converter.loadBin(inBin);
    {
        std::ofstream outHex(f2);
        REQUIRE(outHex.good());
        imploder::HexFile hexFile = converter.binToHex(binFile);
        converter.saveHex(outHex, hexFile);
    }

    std::ifstream inHex(f2);
    REQUIRE(inHex.good());
    imploder::HexFile hexFile = converter.loadHex(inHex);
    binFile = converter.hexToBin(hexFile);
    {
        std::ofstream outBin(f3);
        REQUIRE(outBin.good());
        converter.saveBin(outBin, binFile);
    }

    REQUIRE(fs::file_size(f1) == fs::file_size(f3));

    // std::string chmod = "chmod +x ";
    // chmod += f3;
    // system(chmod.c_str());
    // system(f3);

}

